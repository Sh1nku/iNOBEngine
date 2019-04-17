#pragma once
#include "../systemprogram.h"

class Window;

class RenderSystem : public SystemProgram {
public:
	RenderSystem();
	~RenderSystem();
	void Update(float dt) override;
private:
	Window* window;
};