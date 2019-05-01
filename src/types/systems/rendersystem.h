#pragma once
#include "../systemprogram.h"

class Window;

class RenderSystem : public SystemProgram {
public:
	RenderSystem();
	~RenderSystem();
	void Update(float dt) override;
	void SetBackgroundColor(float r, float g, float b, float a);
private:
	Window* window;
	std::tuple<float, float, float, float> backgroundColor;
};