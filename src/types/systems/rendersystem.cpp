#include "rendersystem.h"
#include "../../io/resources.h"
#include "../../window/window.h"
#include "../component.h"
#include "../components/animation.h"
#include "../components/transform.h"
#include "../components/camera.h"
#include "../gameobject.h"
#include "../../eventmanager.h"

RenderSystem::RenderSystem() {
	mMap.insert({ Component::GetBitcode("Transform") | Component::GetBitcode("Animation"), std::make_unique<gameObject_map>() });
	mMap.insert({ Component::GetBitcode("Camera"), std::make_unique<gameObject_map>() });

	window = new Window();
	window->Create();
	backgroundColor = std::make_tuple(0, 1, 0, 1);
	//Load textures that could not be loaded because glContext did not exist
	for (auto& texture : Resources::textureBacklog) {
		Texture* tempTex = Texture::LoadTexture(texture.first);
		memcpy(texture.second, tempTex, sizeof(Texture));
	}
	//Reload textures that were deleted from a previous context
	for (auto& texturePair : Resources::textures) {
		if (!glIsTexture(texturePair.second->GetID())) {
			Texture* tempTex = Texture::LoadTexture((std::string)texturePair.first);
			memcpy(texturePair.second.get(), tempTex, sizeof(Texture));
		}
	}
	Resources::textureBacklog.clear();
	EventManager::Subscribe("CHANGE_PERSPECTIVE", [&](void* data) {
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
}

RenderSystem::~RenderSystem() {
	delete window;
}

void RenderSystem::Update(float dt) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(std::get<0>(backgroundColor), std::get<1>(backgroundColor), std::get<2>(backgroundColor), std::get<3>(backgroundColor));
	glLoadIdentity();
	for (auto& entry : *GetEntries(Component::GetBitcode("Camera"))) {
		Camera* camera = (Camera*)entry.second->at(Component::GetBitcode("Camera"));
		Transform* transform = camera->GetParent()->transform;
		b2Vec2 pos = transform->GetWorldPosition();
		glPushMatrix();
		if (camera->type == CAMERA_TYPE::PERSPECTIVE) {
			gluLookAt(pos.x, pos.y, transform->GetZCoord(), pos.x, pos.y, 0, 0, 1, 0);
		}
		else {
			glScalef(transform->GetZCoord() / 10, transform->GetZCoord() / 10, transform->GetZCoord() / 10);
			glTranslatef(-pos.x, -pos.y, 0);
		}
	}
	for (auto& entry : *GetEntries(Component::GetBitcode("Animation") | Component::GetBitcode("Transform"))) {
		Animation* anim = (Animation*)entry.second->at(Component::GetBitcode("Animation"));
		Transform* transform = (Transform*)entry.second->at(Component::GetBitcode("Transform"));
		UI32 id = anim->currentClip->texture->GetID();
		b2Vec2& worldPos = transform->GetWorldPosition();
		Texture* tex = anim->currentClip->texture;
		AnimationCoords& coords = anim->currentClip->frames.at(anim->currentFrame).coords;

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, id);
		glTranslatef(worldPos.x, worldPos.y, transform->GetZCoord());
		glRotatef(transform->GetWorldRotation() , 0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(coords.bottomLeft.x / tex->width,coords.bottomLeft.y / tex->height);
		glVertex3f(-.5f, -.5f, 0);
		glTexCoord2f(coords.bottomRight.x / tex->width, coords.bottomRight.y / tex->height);
		glVertex3f(.5f, -.5f, 0);
		glTexCoord2f(coords.topRight.x / tex->width, coords.topRight.y / tex->height);
		glVertex3f(.5f, .5f, 0);
		glTexCoord2f(coords.topLeft.x / tex->width, coords.topLeft.y / tex->height);
		glVertex3f(-.5f, .5f, 0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	SDL_GL_SwapWindow(window->mWindow);
	
}

void RenderSystem::SetBackgroundColor(float r, float g, float b, float a) {
	backgroundColor = std::make_tuple(r, g, b, a);
}