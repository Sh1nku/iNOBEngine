#pragma once
#include "../systemprogram.h"
#include "Box2D/Box2D.h"

class RenderSystem;

class CollisionSystem : public SystemProgram {
public:
	friend class RenderSystem;
	CollisionSystem(b2Vec2 gravity = b2Vec2(0, 0));
	void Update(float dt) override;
	void RemoveFromSystem(UI32 id, GameObject* obj) override;
	b2Vec2 GetGravity();
	void SetGravity(b2Vec2 gravity);
protected:
	b2World world;
};