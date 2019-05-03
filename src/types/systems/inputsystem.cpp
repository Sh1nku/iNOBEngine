#include "inputsystem.h"
#include "../components/input.h"
#include "../../eventmanager.h"

SDL_Event e;

InputSystem::InputSystem() {
	mMap.insert({ Component::GetBitcode("Input"), std::make_unique<gameObject_map>() });
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			auto controller = SDL_GameControllerOpen(i);
			controllers.emplace(i, controller);
			if (controller) {
				break;
			}
			else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}
}

InputSystem::~InputSystem() {
}

void InputSystem::Update(float dt) {
	for (auto& keys : keyCodes) {
		std::get<0>(keys.second) = false;
		std::get<1>(keys.second) = false;
	}
	for (auto& entry : *GetEntries(Component::GetBitcode("Input"))) {
		Input* input = (Input*)entry.second->at(Component::GetBitcode("Input"));
		for (auto& tuple : input->controllerButtons) {
			std::get<0>(tuple) = false;
			std::get<1>(tuple) = false;
		}
	}
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_KEYDOWN:
			{
				if (e.key.repeat == 0) {
					auto keyDown = e.key.keysym.sym;
					try {
						auto& tupleDown = keyCodes.at(keyDown);
						std::get<0>(tupleDown) = true;
						std::get<1>(tupleDown) = false;
						std::get<2>(tupleDown) = true;
					}
					catch (std::out_of_range) {
						keyCodes.emplace(keyDown, std::make_tuple<bool, bool, bool>(true, false, true));
					}
					break;
				}
			}
			case SDL_KEYUP:
			{
				if (e.key.repeat == 0) {
					auto keyUp = e.key.keysym.sym;
					try {
						auto& tupleUp = keyCodes.at(keyUp);
						std::get<0>(tupleUp) = false;
						std::get<1>(tupleUp) = true;
						std::get<2>(tupleUp) = false;
					}
					catch (std::out_of_range) {
						keyCodes.emplace(keyUp, std::make_tuple<bool, bool, bool>(false, true, false));
					}
					break;
				}
			}
			case SDL_CONTROLLERDEVICEADDED:
			{
				break;
			}
			case SDL_CONTROLLERDEVICEREMOVED:
			{
				break;
			}
			case SDL_CONTROLLERBUTTONDOWN:
			{
				for (auto& entry : *GetEntries(Component::GetBitcode("Input"))) {
					Input* input = (Input*) entry.second->at(Component::GetBitcode("Input"));
					if (input->id == -1 || input->id == e.cbutton.which) {
						input->controllerButtons[e.cbutton.button] = std::make_tuple<bool, bool, bool>(true, false, true);
					}
				}
				break;
			}

			case SDL_CONTROLLERBUTTONUP:
			{
				for (auto& entry : *GetEntries(Component::GetBitcode("Input"))) {
					Input* input = (Input*)entry.second->at(Component::GetBitcode("Input"));
					if (input->id == -1 || input->id == e.cbutton.which) {
						input->controllerButtons[e.cbutton.button] = std::make_tuple<bool, bool, bool>(false, true, false);
					}
				}
				break;
			}

			case SDL_CONTROLLERAXISMOTION:
			{
				for (auto& entry : *GetEntries(Component::GetBitcode("Input"))) {
					Input* input = (Input*)entry.second->at(Component::GetBitcode("Input"));
					if (input->id == -1 || input->id == e.cbutton.which) {
						input->controllerAxes[e.caxis.axis] = e.caxis.value;
					}
				}
				break;
			}

			case SDL_QUIT:
			{
				EventManager::FireEvent("QUIT", nullptr);
			}
		}

	}
}