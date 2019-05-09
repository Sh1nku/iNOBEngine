#pragma once
#include "../systemprogram.h"

class Window;
class UIComponent;

class RenderSystem : public SystemProgram {
public:
	RenderSystem();
	~RenderSystem();
	void Update(float dt) override;
	void SetBackgroundColor(float r, float g, float b, float a);
	void SetShowFPS(bool active);
private:
	Window* window;
	std::tuple<float, float, float, float> backgroundColor;
	void StartGUIDraw();
	void EndGUIDraw();
	bool showFPS;
	void ShowFPS();
	void RenderLabel(UIComponent& component);
	void RenderButton(UIComponent& component);
};