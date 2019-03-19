#include "testcomponent.h"
#include <vector>

Component::TYPE TestComponent::GetBitcode() {
	return Component::TYPE::TEST_COMPONENT;
}

void to_json(nlohmann::json& j, const TestComponent& c) {
	j = nlohmann::json{ { "value", c.value }, {"value2", c.value2}, {"position", std::vector<float>{c.position.x,c.position.y} } };
}

void from_json(const nlohmann::json& j, TestComponent& c) {
	j.at("value").get_to(c.value);
	j.at("value2").get_to(c.value2);
	std::vector<float> positionVector;
	j.at("position").get_to(positionVector);
	c.position.x = positionVector[0];
	c.position.y = positionVector[1];
}