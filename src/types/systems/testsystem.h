#pragma once

#include "../../types/systemprogram.h"

class TestSystem : public SystemProgram {
public:
	TestSystem();
	~TestSystem();
	void Update(float dt) override;
private:
};