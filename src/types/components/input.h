#pragma once
#include "../component.h"
#include <unordered_map>
#include "SDL.h"
#include "../vectors.h"

class InputSystem;

class Input : public Component {
public:
	friend class InputSystem;
	Input(GameObject *parent = nullptr) : Component(parent), id(-1) { }
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	bool GetKeyDown(const std::string& key);
	bool GetKeyUp(const std::string& key);
	bool IsKeyPressed(const std::string& key);
	///TODO Implement multiple controllers
	void SetController(I8 id);
	Vec2f GetControllerLeftAxis();
	Vec2f GetControllerRightAxis();
	float GetControllerLeftTrigger();
	float GetControllerRightTrigger();
	bool GetControllerButtonDown(std::string button);
	bool GetControllerButtonUp(std::string button);
	bool IsControllerButtonPressed(std::string button);
	
protected:
	I16 controllerAxes[SDL_CONTROLLER_AXIS_MAX];
	std::tuple<bool, bool, bool> controllerButtons[SDL_CONTROLLER_BUTTON_MAX];
	I8 id;
};

void to_json(nlohmann::json& j, const Input& t);
void from_json(const nlohmann::json& j, Input& t);

constexpr int DEAD_ZONE = 3000;
extern std::unordered_map < SDL_Keycode, std::tuple<bool, bool, bool>> keyCodes;
extern std::unordered_map <UI8, SDL_GameController*> controllers;