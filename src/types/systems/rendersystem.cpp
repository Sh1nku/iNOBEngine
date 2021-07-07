#include <box2d/box2d.h>
#include "rendersystem.h"
#include "../../io/resources.h"
#include "../../window/window.h"
#include "../component.h"
#include "../components/animation.h"
#include "../components/transform.h"
#include "../components/camera.h"
#include "../components/uicomponent.h"
#include "../components/collision.h"
#include "../gameobject.h"
#include "../../eventmanager.h"
#include "imgui.h"
#include "../../window/imgui/imgui_impl_opengl2.h"
#include "../../window/imgui/imgui_impl_sdl.h"
#include "../../manager.h"
#include "collisionsystem.h"
#include "../../window/cef/cef_manager.h"

RenderSystem::RenderSystem() : showFPS(false), showCollisions(false) {

	mMap.insert({ Component::GetBitcode("Transform") | Component::GetBitcode("Animation"), std::make_unique<gameObject_map>() });
	mMap.insert({ Component::GetBitcode("Camera"), std::make_unique<gameObject_map>() });
	mMap.insert({ Component::GetBitcode("UIComponent"), std::make_unique<gameObject_map>() });

	window = new Window();
	window->Create();
	backgroundColor = std::make_tuple(0.f, 1.f, 0.f, 1.f);
	//Load textures that could not be loaded because glContext did not exist
	for (auto& texture : Resources::textureBacklog) {
		Texture* tempTex = Texture::LoadTexture(texture.first);
		memcpy(texture.second, tempTex, sizeof(Texture));
		delete tempTex;
	}
	//Reload textures that were deleted from a previous context
	for (auto& texturePair : Resources::textures) {
		if (!glIsTexture(texturePair.second->GetID())) {
			Texture* tempTex = Texture::LoadTexture((std::string)texturePair.first);
			memcpy(texturePair.second.get(), tempTex, sizeof(Texture));
			delete tempTex;
		}
	}
	Resources::textureBacklog.clear();
	Manager::GetInstance()->Subscribe(nullptr,"CHANGE_PERSPECTIVE", nullptr, [&](void* data) {
		auto& tuple = *(std::tuple <CAMERA_TYPE, UI16, float, float >*) data;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (std::get<0>(tuple) == ORTHOGRAPHIC) {
			glOrtho(-(Window::SCREEN_WIDTH / ((float)Window::SCREEN_HEIGHT)), (Window::SCREEN_WIDTH / ((float)Window::SCREEN_HEIGHT)), -1, 1, std::get<2>(tuple), std::get<3>(tuple));
		}
		else {
			gluPerspective(std::get<1>(tuple), ((float)Window::SCREEN_WIDTH) / Window::SCREEN_HEIGHT, (std::get<2>(tuple) > 0 ? std::get<2>(tuple) : 0.01), std::get<3>(tuple));
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		delete data;
	});
	if (CEF_INITIALIZED) {
		{
			CefMainArgs args;
			CefSettings settings;
			std::ostringstream ss;
			ss << SDL_GetBasePath() << "locales/";
			CefString(&settings.locales_dir_path) = ss.str();
			CefString(&settings.resources_dir_path) = SDL_GetBasePath();
			settings.no_sandbox = true;
			settings.windowless_rendering_enabled = true;

			CefInitialize(args, settings, nullptr, nullptr);
		}
		GUIrenderHandler = new GUIRenderHandler();
		{
			CefWindowInfo window_info;
			CefBrowserSettings browserSettings;
			window_info.SetAsWindowless(NULL, true); // false means no transparency (site background colour)
			GUIbrowserClient = new GUIBrowserClient(GUIrenderHandler);
			std::string url = "file:///" + Resources::gameDirAbsoulute + "ui.html";
			GUIbrowser = CefBrowserHost::CreateBrowserSync(window_info, GUIbrowserClient.get(), url, browserSettings, nullptr);
		}
	}
	else {
		std::cout << "Warning: CEF is not initialized";
	}
}

RenderSystem::~RenderSystem() {
	if (CEF_INITIALIZED) {
		GUIbrowser->GetHost()->CloseBrowser(true);
		while (GUIbrowser->HasOneRef()) {
			CefDoMessageLoopWork();
		}
		GUIbrowser = nullptr;
		GUIbrowserClient = nullptr;
		GUIrenderHandler = nullptr;
		CefShutdown();
	}
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	delete window;
}

void RenderSystem::Update(float dt) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(std::get<0>(backgroundColor), std::get<1>(backgroundColor), std::get<2>(backgroundColor), std::get<3>(backgroundColor));
	glLoadIdentity();

	for (auto& entry : *GetEntries(Component::GetBitcode("Camera"))) {
		if (entry.first->active) {
			Camera* camera = (Camera*)entry.second->at(Component::GetBitcode("Camera"));
			Transform* transform = camera->GetParent()->transform;
			auto pos = transform->GetWorldPosition();
			glPushMatrix();
			if (camera->type == CAMERA_TYPE::PERSPECTIVE) {
				gluLookAt(pos.x, pos.y, pos.z, pos.x, pos.y, 0, 0, 1, 0);
			}
			else {
				glScalef(pos.z / 10, pos.z / 10, pos.z / 10);
				glTranslatef(-pos.x, -pos.y, 0);
			}
		}
	}
	for (auto& entry : *GetEntries(Component::GetBitcode("Animation") | Component::GetBitcode("Transform"))) {
		if (entry.first->active) {
			Animation* anim = (Animation*)entry.second->at(Component::GetBitcode("Animation"));
			Transform* transform = (Transform*)entry.second->at(Component::GetBitcode("Transform"));
			UI32 id = anim->currentClip->texture->GetID();
			const auto& worldPos = transform->GetWorldPosition();
			Texture* tex = anim->currentClip->texture;
			AnimationCoords& coords = anim->currentClip->frames.at(anim->currentFrame).coords;

			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, id);
			glTranslatef(worldPos.x, worldPos.y, worldPos.z);
			glRotatef((transform->GetWorldRotation() * RADIAN_IN_DEGREES), 0, 0, 1);
			UI32 width = coords.bottomRight.x - coords.bottomLeft.x;
			UI32 height = coords.bottomRight.y - coords.topRight.y;
			float scale = transform->GetScale();
			glBegin(GL_QUADS);
			glColor4f(1, 1, 1, 1);
			glTexCoord2f(coords.bottomLeft.x / tex->width, coords.bottomLeft.y / tex->height);
			glVertex3f(-.5f * scale * width / pixelsPerUnit, -.5f * scale * height / pixelsPerUnit, 0);
			glTexCoord2f(coords.bottomRight.x / tex->width, coords.bottomRight.y / tex->height);
			glVertex3f(.5f * scale * width / pixelsPerUnit, -.5f * scale * height / pixelsPerUnit, 0);
			glTexCoord2f(coords.topRight.x / tex->width, coords.topRight.y / tex->height);
			glVertex3f(.5f * scale * width / pixelsPerUnit, .5f * scale * height / pixelsPerUnit, 0);
			glTexCoord2f(coords.topLeft.x / tex->width, coords.topLeft.y / tex->height);
			glVertex3f(-.5f * scale * width / pixelsPerUnit, .5f * scale * height / pixelsPerUnit, 0);
			glEnd();
			glPopMatrix();
		}
	}
	if (showCollisions) {
		ShowCollisions();
	}
	StartGUIDraw();


	if (CEF_INITIALIZED) {
		CefDoMessageLoopWork();
		if (GUIrenderHandler->texture && !GUIbrowser->IsLoading()) {
			GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
			GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
			GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
			GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
			glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
			glDisable(GL_DEPTH_TEST);

			glViewport(0, 0, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, 0, -1.0f, +1.0f);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();


			glPushMatrix();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-1, 1, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glColor3f(1, 1, 1);
			glBindTexture(GL_TEXTURE_2D, GUIrenderHandler->texture->id);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(1.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glEnable(GL_DEPTH_TEST);
			glBindTexture(GL_TEXTURE_2D, (GLuint)last_texture);
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glPopAttrib();
			glPolygonMode(GL_FRONT, (GLenum)last_polygon_mode[0]); glPolygonMode(GL_BACK, (GLenum)last_polygon_mode[1]);
			glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
			glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
		}
	}

	/*if (showFPS) {
		ShowFPS();
	}
	for (auto& entry : *GetEntries(Component::GetBitcode("UIComponent"))) {
		if (entry.first->active) {
			UIComponent* ui = (UIComponent*)entry.second->at(Component::GetBitcode("UIComponent"));
			if (ui->type == UI_TYPE::LABEL) {
				RenderLabel(*ui);
			}
			else {
				RenderButton(*ui);
			}
		}
	}*/
	EndGUIDraw();

	glPopMatrix();
	SDL_GL_SwapWindow(window->mWindow);
	
}

void RenderSystem::SetBackgroundColor(float r, float g, float b, float a) {
	backgroundColor = std::make_tuple(r, g, b, a);
}

void RenderSystem::StartGUIDraw() {
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(Window::mWindow);
	ImGui::NewFrame();
}

void RenderSystem::EndGUIDraw() {
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void RenderSystem::SetShowFPS(bool active) {
	showFPS = active;
}

void RenderSystem::SetShowCollisions(bool active) {
	showCollisions = active;
}

void RenderSystem::ShowCollisions() {
	CollisionSystem* collisionSystem = Manager::GetInstance()->GetSystem<CollisionSystem>();
	if (collisionSystem != nullptr) {
		collisionSystem->world.SetDebugDraw(&collisionDrawer);
		collisionDrawer.SetFlags(b2Draw::e_shapeBit);
		collisionSystem->world.DebugDraw();
	}
}

void RenderSystem::ShowFPS() {
	ImGui::SetNextWindowPos(ImVec2(0, 0) , ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(90,20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("FPSCounter", nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}

void RenderSystem::RenderLabel(UIComponent& component) {
	ImGui::SetNextWindowPos(component.GetPosition(), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(component.GetSize(), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin(component.windowID.c_str(), nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);
	ImGui::Text(component.GetText().c_str(), ImGui::GetIO().Framerate);
	ImGui::End();
}

void RenderSystem::RenderButton(UIComponent& component) {
	ImGui::SetNextWindowPos(component.GetPosition(), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(component.GetSize(), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin(component.windowID.c_str(), nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);
	if (ImGui::Button(component.GetText().c_str(), ImGui::GetContentRegionAvail())) {
		Manager::GetInstance()->FireEvent(component.GetParent(),component.buttonEvent,(void*)"Test text");
	}
	ImGui::End();
}