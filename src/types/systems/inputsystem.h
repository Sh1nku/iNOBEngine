#pragma once
#include "../systemprogram.h"

class InputSystem : public SystemProgram {
public:
	InputSystem();
	~InputSystem();
	void Update(float dt) override;
private:
};