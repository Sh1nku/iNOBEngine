#pragma once
#include "../systemprogram.h"

class ScriptSystem : public SystemProgram {
public:
	ScriptSystem();
	~ScriptSystem();
	void Update(float dt) override;
private:
};