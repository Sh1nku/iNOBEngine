#pragma once
#include "../component.h"
#include "Box2D/Box2D.h"

class Transform : public Component {
public:
	Transform(GameObject *parent = nullptr) : Component(parent) { mWorldPosition = b2Vec2(0, 0); }
	Component::TYPE GetBitcode() override;
	b2Vec2 GetWorldPosition();
	b2Vec2 GetLocalPosition();
	void SetLocalPosition(b2Vec2* position);
	void SetWorldPosition(b2Vec2* position);

private:
	b2Vec2 mWorldPosition;
};

void to_json(nlohmann::json& j, const Transform& t);
void from_json(const nlohmann::json& j, Transform& t);