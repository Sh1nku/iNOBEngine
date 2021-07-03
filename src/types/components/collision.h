#pragma once

#include "../component.h"
#include "box2d/box2d.h"
#include "../vectors.h"

class Collision : public Component {
public:
	friend class CollisionSystem;
	friend class Transform;
	friend void from_json(const nlohmann::json& j, Collision& t);
	friend void to_json(nlohmann::json& j, const Collision& t);
	Collision(GameObject *parent = nullptr);
	~Collision();
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	void SetLinearVelocity(Vec2f vel);
	void SetAngularVelocity(float vel);
	void SetCollisionFunc(std::function<void(Collision*)> func);
	b2Body *body;
	b2Shape* cloneB2Shape(b2Shape* shape);
protected:
	b2BodyDef bodyDef;
	std::vector<b2FixtureDef> fixtures;
	std::function<void(Collision*)> collisionFunc;
	void SetScale(float scale);
	float mScale;
};

UI16 stringToBin(std::string str);
static b2BlockAllocator blockAllocator;

void to_json(nlohmann::json& j, const Collision& t);
void from_json(const nlohmann::json& j, Collision& t);