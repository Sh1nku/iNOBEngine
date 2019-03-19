#pragma once
#include "../systemprogram.h"

class Window;

class RenderSystem : SystemProgram {
public:
	RenderSystem();
	~RenderSystem();
private:
	Window* window;
};