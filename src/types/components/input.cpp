#include "input.h"

std::unordered_map < SDL_Keycode, std::tuple<bool, bool, bool>> keyCodes;

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

Component* Input::Clone(GameObject* parent) {
	return new Input(parent);
}

UI32 Input::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Input");
	return bitcode;
}

const auto x = [&] {
	Component::AddBitcode("Input");
	jsonComponentList.emplace("Input", &CreateComponent<Input>);
	return true;
}();

void to_json(nlohmann::json& j, const Input& t) {

}

void from_json(const nlohmann::json& j, Input& t) {

}