#include "rendersystem.h"
#include "window/window.h"
#include "../component.h"

RenderSystem::RenderSystem() {
	mMap.insert({ Component::TYPE::TRANSFORM, std::make_unique<gameObject_map>() });

	window = new Window();
	window->Create();
}

RenderSystem::~RenderSystem() {
	delete window;
}