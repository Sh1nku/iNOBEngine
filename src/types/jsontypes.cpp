#include "jsontypes.h"

void to_json(nlohmann::json& j, const b2Vec2& t) {

}

void from_json(const nlohmann::json& j, b2Vec2& t) {
	std::vector<float> floats;
	j.get_to(floats);
	t.x = floats.at(0);
	t.y = floats.at(1);
}

void to_json(nlohmann::json& j, const Vec2f& t) {

}

void from_json(const nlohmann::json& j, Vec2f& t) {
	std::vector<float> floats;
	j.get_to(floats);
	t.x = floats.at(0);
	t.y = floats.at(1);
}

void to_json(nlohmann::json& j, const Vec3f& t) {

}

void from_json(const nlohmann::json& j, Vec3f& t) {
	std::vector<float> floats;
	j.get_to(floats);
	t.x = floats.at(0);
	t.y = floats.at(1);
	if (floats.size() > 2) {
		t.z = floats.at(2);
	}
}