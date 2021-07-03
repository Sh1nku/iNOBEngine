#include "input.h"
#include "../systems/inputsystem.h"

std::unordered_map < SDL_Keycode, std::tuple<bool, bool, bool>> keyCodes;
std::unordered_map <UI8, SDL_GameController*> controllers;

bool Input::GetKeyDown(std::string key) {
	try {
		SDL_Keycode keyCode = SDL_GetKeyFromName(key.c_str());
		auto[down, up, continuous] = keyCodes.at(keyCode);
		return down;
	}
	catch (std::out_of_range) {
		return false;
	}
}

bool Input::GetKeyUp(std::string key) {
	try {
		SDL_Keycode keyCode = SDL_GetKeyFromName(key.c_str());
		auto[down, up, continuous] = keyCodes.at(keyCode);
		return up;
	}
	catch (std::out_of_range) {
		return false;
	}
}

bool Input::IsKeyPressed(std::string key) {
	try {
		SDL_Keycode keyCode = SDL_GetKeyFromName(key.c_str());
		auto[down, up, continuous] = keyCodes.at(keyCode);
		return continuous;
	}
	catch (std::out_of_range) {
		return false;
	}
}

bool Input::GetControllerButtonDown(std::string button) {
	auto id = SDL_GameControllerGetButtonFromString(button.c_str());
 	return std::get<0>(controllerButtons[id]);
}

bool Input::GetControllerButtonUp(std::string button) {
	auto id = SDL_GameControllerGetButtonFromString(button.c_str());
	return std::get<1>(controllerButtons[id]);
}

bool Input::IsControllerButtonPressed(std::string button) {
	auto id = SDL_GameControllerGetButtonFromString(button.c_str());
	return std::get<2>(controllerButtons[id]);
}

Vec2f Input::GetControllerLeftAxis() {
	float x = 0, y = 0;
	if (controllerAxes[SDL_CONTROLLER_AXIS_LEFTX] > DEAD_ZONE || controllerAxes[SDL_CONTROLLER_AXIS_LEFTX] < -DEAD_ZONE) {
		x = controllerAxes[SDL_CONTROLLER_AXIS_LEFTX] / ((float)INT16_MAX);
	}
	if (controllerAxes[SDL_CONTROLLER_AXIS_LEFTY] > DEAD_ZONE || controllerAxes[SDL_CONTROLLER_AXIS_LEFTY] < -DEAD_ZONE) {
		y = controllerAxes[SDL_CONTROLLER_AXIS_LEFTY] / ((float)INT16_MAX);
	}
	Vec2f vec(x,y);
	float length = glm::length(vec);
	vec.x = vec.x / length;
	vec.y = vec.y / length;
	return vec;
}

Vec2f Input::GetControllerRightAxis() {
	float x = 0, y = 0;
	if (controllerAxes[SDL_CONTROLLER_AXIS_RIGHTX] > DEAD_ZONE || controllerAxes[SDL_CONTROLLER_AXIS_RIGHTX] < -DEAD_ZONE) {
		x = controllerAxes[SDL_CONTROLLER_AXIS_RIGHTX] / ((float)INT16_MAX);
	}
	if (controllerAxes[SDL_CONTROLLER_AXIS_RIGHTY] > DEAD_ZONE || controllerAxes[SDL_CONTROLLER_AXIS_RIGHTY] < -DEAD_ZONE) {
		y = controllerAxes[SDL_CONTROLLER_AXIS_RIGHTY] / ((float)INT16_MAX);
	}
	Vec2f vec(x, y);
	float length = glm::length(vec);
	vec.x = vec.x / length;
	vec.y = vec.y / length;
	return vec;
}

float Input::GetControllerLeftTrigger() {
	float x = 0;
	if (controllerAxes[SDL_CONTROLLER_AXIS_TRIGGERLEFT] > DEAD_ZONE || controllerAxes[SDL_CONTROLLER_AXIS_TRIGGERLEFT] < -DEAD_ZONE) {
		x = controllerAxes[SDL_CONTROLLER_AXIS_TRIGGERLEFT] / ((float)INT16_MAX);
	}
	return x;
}

float Input::GetControllerRightTrigger() {
	float y = 0;
	if (controllerAxes[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] > DEAD_ZONE || controllerAxes[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] < -DEAD_ZONE) {
		y = controllerAxes[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] / ((float)INT16_MAX);
	}
	return y;
}

void Input::SetController(I8 id) {

}

Component* Input::Clone(GameObject* parent) {
	return new Input(parent);
}

UI32 Input::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Input");
	return bitcode;
}

const auto x = [] {
	AddComponentToList<Input>("Input");
	return true;
}();

void to_json(nlohmann::json& j, const Input& t) {

}

void from_json(const nlohmann::json& j, Input& t) {

}