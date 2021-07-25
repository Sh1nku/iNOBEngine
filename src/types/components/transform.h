#pragma once
#include "../component.h"
#include "box2d/box2d.h"
#include "../vectors.h"

class Transform : public Component {
public:
	Transform(GameObject *parent = nullptr) : Component(parent), mWorldPosition(Vec3f(0,0,0)), mWorldRotation(0),  mScale(1), mScreenPosition(Vec2f(0,0)) {}
	Transform(Vec3f position, float rotation, GameObject *parent = nullptr) : Component(parent), mWorldPosition(position), mWorldRotation(rotation), mScale(1), mScreenPosition(Vec2f(0, 0)) {};
	Component* Clone(GameObject* parent);
	Vec3f GetWorldPosition() const;
	Vec3f GetLocalPosition() const;
	const Vec2f& GetScreenPosition() const;
	float GetWorldRotation() const;
	float GetLocalRotation() const;
	float GetScale() const;
	void SetLocalPosition(const Vec3f& position);
	void SetScreenPosition(const Vec2f& position);
	///TODO Implement, and make sure works with child objects like in SetLocalPosition
	//void SetLocalRotation(float rotation);
	void SetWorldPosition(const Vec3f& position);
	void SetWorldRotation(float rotation);
	void SetScale(float scale);
	UI32 GetBitcode() override;

private:
	void UpdatePosition(Vec3f* oldPos);

	Vec3f mWorldPosition;
	Vec2f mScreenPosition;
	float mWorldRotation;
	float mScale;
};

void to_json(nlohmann::json& j, const Transform& t);
void from_json(const nlohmann::json& j, Transform& t);