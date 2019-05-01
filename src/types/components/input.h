#pragma once
#include "../component.h"
#include <unordered_map>
#include "SDL.h"

class Input : public Component {
public:
	Input(GameObject *parent = nullptr) : Component(parent) { }
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	bool GetKeyDown(std::string key);
	bool GetKeyUp(std::string key);
	bool IsKeyPressed(std::string key);

private:
	
};

void to_json(nlohmann::json& j, const Input& t);
void from_json(const nlohmann::json& j, Input& t);

extern std::unordered_map < SDL_Keycode, std::tuple<bool, bool, bool>> keyCodes;