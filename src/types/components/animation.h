#pragma once
#include "../component.h"
#include "io/texture.h"
#include "Box2D/Box2D.h"

class Animation : public Component {
public:
	Animation(GameObject *parent = nullptr);
	UI32 GetBitcode() override;
	void SetClip(std::string& name);
	AnimationClip* currentClip;
	int currentFrame;

private:
};

void to_json(nlohmann::json& j, const Animation& t);
void from_json(const nlohmann::json& j, Animation& t);