#pragma once
#include "../systemprogram.h"
#include "Box2D/Box2D.h"
#include "../vectors.h"

class RenderSystem;

class CollisionSystem : public SystemProgram {
public:
	friend class RenderSystem;
	CollisionSystem(Vec2f gravity = Vec2f(0, 0));
	void Update(float dt) override;
	void RemoveFromSystem(UI32 id, GameObject* obj) override;
	Vec2f GetGravity();
	void SetGravity(Vec2f gravity);
protected:
	b2World world;
};