#pragma once
#include "../component.h"
#include "Box2D/Box2D.h"

class Transform : public Component {
public:
	Transform(GameObject *parent = nullptr) : Component(parent), mWorldPosition(b2Vec2(0,0)), mWorldRotation(0) {}
	Transform(b2Vec2 position, float rotation, GameObject *parent = nullptr) : Component(parent), mWorldPosition(position), mWorldRotation(rotation) {};
	b2Vec2 GetWorldPosition() const;
	b2Vec2 GetLocalPosition() const;
	float GetWorldRotation() const;
	float GetLocalRotation() const;
	void SetLocalPosition(b2Vec2* position);
	void SetWorldPosition(b2Vec2* position);
	UI32 GetBitcode() override;

private:
	b2Vec2 mWorldPosition;
	float mWorldRotation;
};

void to_json(nlohmann::json& j, const Transform& t);
void from_json(const nlohmann::json& j, Transform& t);