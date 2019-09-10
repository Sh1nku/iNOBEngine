#include "uicomponent.h"
#include "../../window/window.h"

static UI32 staticWindowID = 0;

std::string UIComponent::GetNewWindowID() {
	return std::to_string(staticWindowID++);
}

UIComponent::UIComponent(GameObject *parent) : Component(parent),
positionX(FLT_MAX), positionY(FLT_MAX), positionPercentX(FLT_MAX), positionPercentY(FLT_MAX),
sizeX(FLT_MAX), sizeY(FLT_MAX), sizePercentX(FLT_MAX), sizePercentY(FLT_MAX) {
	
}

Component* UIComponent::Clone(GameObject* parent) {
	UIComponent* component = new UIComponent();
	component->mParent = parent;
	component->positionX = positionX; component->positionY = positionY;
	component->positionPercentX = positionPercentX; component->positionPercentY = positionPercentY;
	component->sizeX = sizeX; component->sizeY = sizeY;
	component->buttonEvent = buttonEvent;
	return component;
}

UI32 UIComponent::GetBitcode() {
	static UI32 bitcode = bitcodes.at("UIComponent");
	return bitcode;
}

const auto x = [&] {
	AddComponentToList<UIComponent>("UIComponent");
	return true;
}();

ImVec2 UIComponent::GetPosition() {
	return ImVec2((positionX == FLT_MAX ? (Window::SCREEN_WIDTH / 100.0)*positionPercentX : positionX),
		(positionY == FLT_MAX ? (Window::SCREEN_HEIGHT / 100.0)*positionPercentY : positionY));
}

ImVec2 UIComponent::GetSize() {
	return ImVec2((sizeX == FLT_MAX ? (Window::SCREEN_WIDTH / 100.0)*sizePercentX : sizeX),
		(sizeY == FLT_MAX ? (Window::SCREEN_WIDTH / 100.0)*sizePercentY : sizeY));
}

std::string& UIComponent::GetText() {
	return text;
}

void UIComponent::SetText(std::string& text) {
	this->text = text.c_str();
}

void to_json(nlohmann::json& j, const UIComponent& t) {
	j = nlohmann::json{ {"name", "UIComponent"} };
}

std::pair<bool, float> GetCoordsFromString(std::string str) {
	if (str.find("%") != std::string::npos) {
		return std::make_pair(true,std::stof(str.substr(0, str.find("%"))));
	}
	else if (str.find("px") != std::string::npos) {
		return std::make_pair(false, std::stof(str.substr(0, str.find("px"))));
	}
	else {
		return std::make_pair(false, std::stof(str));
	}
}

UI_TYPE UIComponent::GetTypeFromString(std::string type) {
	if (type == "label") {
		return LABEL;
	}
	else {
		return BUTTON;
	}
}

void from_json(const nlohmann::json& j, UIComponent& t) {
	auto& text = j.find("text");
	if (text != j.end()) {
		t.SetText((std::string)text.value());
	}

	std::vector<std::string> position;
	j.at("position").get_to(position);
	std::vector<std::string> size;
	j.at("size").get_to(size);
	auto& posX = GetCoordsFromString(position[0]);
	if (posX.first == false) {
		t.positionX = posX.second;
	}
	else {
		t.positionPercentX = posX.second;
	}

	auto& posY = GetCoordsFromString(position[1]);
	if (posY.first == false) {
		t.positionY = posY.second;
	}
	else {
		t.positionPercentY = posY.second;
	}

	auto& sizeX = GetCoordsFromString(size[0]);
	if (sizeX.first == false) {
		t.sizeX = sizeX.second;
	}
	else {
		t.sizePercentX = sizeX.second;
	}

	auto& sizeY = GetCoordsFromString(size[1]);
	if (sizeY.first == false) {
		t.sizeY = sizeY.second;
	}
	else {
		t.sizePercentY = sizeY.second;
	}

	t.type = UIComponent::GetTypeFromString(j.at("type"));
	t.windowID = UIComponent::GetNewWindowID();

	auto& buttonListener = j.find("buttonevent");
	if (buttonListener != j.end()) {
		t.buttonEvent = buttonListener.value();
	}

}