#pragma once
#include "../systemprogram.h"


class AnimationSystem : public SystemProgram {
public:
	AnimationSystem();
	void Update(float dt) override;
	UI16 frameRate = 60;
private:

};