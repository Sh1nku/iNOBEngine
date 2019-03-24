#pragma once
#include "../component.h"

class Animation : public Component {
public:
	Animation(GameObject *parent = nullptr) : Component(parent) { }
	TYPE GetBitcode() override;
};

void to_json(nlohmann::json& j, const Animation& t);
void from_json(const nlohmann::json& j, Animation& t);