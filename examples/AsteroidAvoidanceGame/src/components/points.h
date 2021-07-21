#pragma once
#include "iNOBEngine.h"

class Points : public Component {
public:
	Points(GameObject* parent = nullptr) : Component(parent), mPoints(0) { }
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	void SetPoints(I16 points);
	const I16& GetPoints() const;

private:
	I16 mPoints;
};

void to_json(nlohmann::json& j, const Points& t);
void from_json(const nlohmann::json& j, Points& t);