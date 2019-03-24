#include "rendersystem.h"
#include "window/window.h"
#include "../component.h"

RenderSystem::RenderSystem() {
	mMap.insert({ Component::TYPE::TRANSFORM, new std::unordered_map<GameObject*,std::unordered_map<UI32,Component*>*>() });

	window = new Window();
	window->Create();
}

RenderSystem::~RenderSystem() {
	delete window;
}