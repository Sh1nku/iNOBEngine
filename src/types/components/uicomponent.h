#pragma once
#include "../component.h"
#include "imgui.h"

enum UI_TYPE {
	LABEL,
	BUTTON
};

class UIComponent : public Component {
public:
	UIComponent(GameObject *parent = nullptr);
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	ImVec2 GetPosition();
	ImVec2 GetSize();
	std::string& GetText();
	static UI_TYPE GetTypeFromString(std::string text);
	static std::string GetNewWindowID();
	void SetText(std::string& text);
	float positionX, positionY;
	float positionPercentX, positionPercentY;
	float sizeX, sizeY;
	float sizePercentX, sizePercentY;
	UI_TYPE type;
	std::string windowID;
	std::string buttonEvent;
private:
	std::string text;
};