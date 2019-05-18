#include "jsontypes.h"

void to_json(nlohmann::json& j, const b2Vec2& t) {

}

void from_json(const nlohmann::json& j, b2Vec2& t) {
	std::vector<float> floats;
	j.get_to(floats);
	t.x = floats.at(0);
	t.y = floats.at(1);
}