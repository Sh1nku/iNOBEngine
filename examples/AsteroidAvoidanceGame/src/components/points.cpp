#include "points.h"

Component* Points::Clone(GameObject* parent) {
	Points* points = new Points();
	points->mParent = parent;
	points->mPoints = this->mPoints;
	return points;
}

UI32 Points::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Points");
	return bitcode;
}

void Points::SetPoints(I16 points)
{
	this->mPoints = points;
}

const I16& Points::GetPoints() const
{
	return mPoints;
}

const auto x = [] {
	AddComponentToList<Points>("Points");
	return true;
}();

void to_json(nlohmann::json& j, const Points& t) {
	j = nlohmann::json{ {"name", "Points"} };
}

void from_json(const nlohmann::json& j, Points& t) {
	const auto& points = j.find("points");
	if (points != j.end()) {
		t.SetPoints(points.value());
	}
}