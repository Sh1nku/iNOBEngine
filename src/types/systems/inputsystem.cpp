#include "inputsystem.h"
#include "../components/input.h"

SDL_Event e;

InputSystem::InputSystem() {
	mMap.insert({ Component::GetBitcode("Input"), std::make_unique<gameObject_map>() });
}

InputSystem::~InputSystem() {
}

void InputSystem::Update(float dt) {
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_KEYDOWN:
			{
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
			case SDL_KEYUP:
			{
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

	}
}