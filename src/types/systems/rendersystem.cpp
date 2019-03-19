#include "rendersystem.h"
#include "window\window.h"
#include "../component.h"

RenderSystem::RenderSystem() {
	mMap.emplace( Component::TYPE::TRANSFORM, new std::vector<std::vector<Component*>*>());

	window = new Window();
	window->Create();
}

RenderSystem::~RenderSystem() {
	delete window;
}