#include "testcomponent.h"
#include <vector>

Component* TestComponent::Clone(GameObject* parent) {
	TestComponent* component = new TestComponent();
	component->mParent = parent;
	component->value = value;
	component->value2 = value2.c_str();
	component->position = position;
	return component;
}

UI32 TestComponent::GetBitcode() {
	static UI32 bitcode = Component::GetBitcode("TestComponent");
	return bitcode;
}

const auto x = [] {
	AddComponentToList<TestComponent>("TestComponent");
	return true;
}();

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