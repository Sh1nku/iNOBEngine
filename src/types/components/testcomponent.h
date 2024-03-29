#pragma once

#include "../component.h"
#include "box2d/box2d.h"

class TestComponent : public Component {
public:
	TestComponent() { value = 0; value2 = ""; position = b2Vec2(0, 0); }
	TestComponent(int value, std::string value2, b2Vec2 position) : value(value), value2(value2), position(position) {}
	Component* Clone(GameObject* parent);
	UI32 GetBitcode() override;
	int value;
	std::string value2;
	b2Vec2 position;
private:
};

void to_json(nlohmann::json& j, const TestComponent& c);
void from_json(const nlohmann::json& j, TestComponent& c);