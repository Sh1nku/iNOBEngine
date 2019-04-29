#pragma once
#include "../component.h"

class Camera : public Component {
public:
	Camera(GameObject *parent = nullptr) : Component(parent) { }
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
};

void to_json(nlohmann::json& j, const Camera& t);
void from_json(const nlohmann::json& j, Camera& t);