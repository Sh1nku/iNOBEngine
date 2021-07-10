#pragma once
#include "../systemprogram.h"
#include "../collisiondebugdraw.h"
#include "../../window/cef/guibrowserclient.h"
#include "../../window/cef/guirenderhandler.h"

class Window;
class UIComponent;

class RenderSystem : public SystemProgram {
public:
	RenderSystem();
	~RenderSystem();
	void Update(float dt) override;
	void SetBackgroundColor(float r, float g, float b, float a);
	void SetShowFPS(bool active);
	void SetShowCollisions(bool active);
	void ExecuteJavascript(const std::string& script);
	void LoadURL(const std::string& url);
	UI16 pixelsPerUnit = 32;
private:
	Window* window;
	std::tuple<float, float, float, float> backgroundColor;
	void StartGUIDraw();
	void EndGUIDraw();
	bool showFPS;
	void ShowFPS(float dt);
	bool showCollisions;
	void ShowCollisions();
	void RenderLabel(UIComponent& component);
	void RenderButton(UIComponent& component);
	CollisionDebugDraw collisionDrawer;

};

const static float RADIAN_IN_DEGREES = 57.3f;