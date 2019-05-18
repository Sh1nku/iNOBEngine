#pragma once
#include "../component.h"
#include "Box2D/Box2D.h"

class Transform : public Component {
public:
	Transform(GameObject *parent = nullptr) : Component(parent), mWorldPosition(b2Vec2(0,0)), mWorldRotation(0), zCoord(0), mScale(1) {}
	Transform(b2Vec2 position, float rotation, float zCoord, GameObject *parent = nullptr) : Component(parent), mWorldPosition(position), zCoord(zCoord), mWorldRotation(rotation), mScale(1) {};
	Component* Clone(GameObject* parent);
	b2Vec2 GetWorldPosition() const;
	b2Vec2 GetLocalPosition() const;
	float GetWorldRotation() const;
	float GetLocalRotation() const;
	float GetZCoord() const;
	float GetScale() const;
	void SetLocalPosition(b2Vec2* position);
	void SetWorldPosition(b2Vec2* position);
	void SetWorldRotation(float rotation);
	void SetZCoord(float zCoord);
	void SetScale(float scale);
	UI32 GetBitcode() override;

private:
	b2Vec2 mWorldPosition;
	float mWorldRotation;
	float zCoord;
	float mScale;
};

void to_json(nlohmann::json& j, const Transform& t);
void from_json(const nlohmann::json& j, Transform& t);