#include "rendersystem.h"
#include "window/window.h"
#include "../component.h"
#include "../components/animation.h"
#include "../components/transform.h"

RenderSystem::RenderSystem() {
	mMap.insert({ Component::GetBitcode("Transform") | Component::GetBitcode("Animation"), std::make_unique<gameObject_map>() });

	window = new Window();
	window->Create();
}

RenderSystem::~RenderSystem() {
	delete window;
}

void RenderSystem::Update(float dt) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 1.f, 1.f);
	//gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	for (auto& entry : *GetEntries(Component::GetBitcode("Animation") | Component::GetBitcode("Transform"))) {
		Animation* anim = (Animation*)entry.second->at(Component::GetBitcode("Animation"));
		Transform* transform = (Transform*)entry.second->at(Component::GetBitcode("Transform"));
		glBegin(GL_TRIANGLES);
		glColor4f(0, 1, 0, 1);
		glVertex3f(-1, -1, -5);
		glVertex3f(1, -1, -5);
		glVertex3f(0, 1, -5);
		glEnd();
	}
	SDL_GL_SwapWindow(window->mWindow);
	
}