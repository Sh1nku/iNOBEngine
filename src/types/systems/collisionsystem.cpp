#include "collisionsystem.h"
#include "../components/collision.h"
#include "../gameobject.h"
#include "../../manager.h"

CollisionSystem::CollisionSystem(Vec2f gravity) : world(Vec2fToB2Vec2(gravity)) {
	mMap.insert({ Component::GetBitcode("Collision") | Component::GetBitcode("Transform"), std::make_unique<gameObject_map>() });
};

void CollisionSystem::Update(float dt) {
	for (auto& entry : *GetEntries(Component::GetBitcode("Collision") | Component::GetBitcode("Transform"))) {
		if (entry.first->active) {
			Collision* collision = (Collision*)entry.second->at(Component::GetBitcode("Collision"));
			Transform* transform = (Transform*)entry.second->at(Component::GetBitcode("Transform"));
			if (collision->body == nullptr) {
				collision->body = world.CreateBody(&collision->bodyDef);
				for (auto& fixture : collision->fixtures) {
					collision->body->CreateFixture(&fixture);
				}
			}
			collision->body->SetEnabled(true);
			auto worldPosition = Vec3fToB2Vec2(transform->GetWorldPosition());
			if ((b2Vec2)collision->body->GetPosition() != worldPosition || collision->body->GetAngle() != transform->GetWorldRotation()) {
				collision->body->SetTransform(worldPosition, transform->GetWorldRotation());
			}
		}
		else {
			Collision* collision = (Collision*)entry.second->at(Component::GetBitcode("Collision"));
			if (collision->body != nullptr) {
				collision->body->SetEnabled(false);
			}
		}
	}
	world.Step(dt, 8, 3);
	for (auto& entry : *GetEntries(Component::GetBitcode("Collision") | Component::GetBitcode("Transform"))) {
		if (entry.first->active) {
			Collision* collision = (Collision*)entry.second->at(Component::GetBitcode("Collision"));
			Transform* transform = (Transform*)entry.second->at(Component::GetBitcode("Transform"));
			if (collision->body != nullptr) {
				auto worldPosition = Vec3fToB2Vec2(transform->GetWorldPosition());
				if (collision->body->GetPosition() != worldPosition || collision->body->GetAngle() != transform->GetWorldRotation()) {
					auto newPos = Vec3f(collision->body->GetPosition().x, collision->body->GetPosition().y, transform->GetWorldPosition().z);
					transform->SetWorldPosition((Vec3f*)&newPos); 
					transform->SetWorldRotation(collision->body->GetAngle());
				}
			}
		}
	}
	for (b2Contact* c = world.GetContactList(); c; c = c->GetNext()) {
		if (((Collision*)c->GetFixtureA()->GetBody()->GetUserData().pointer)->collisionFunc != nullptr) {
			((Collision*)c->GetFixtureA()->GetBody()->GetUserData().pointer)->collisionFunc(((Collision*)c->GetFixtureB()->GetBody()->GetUserData().pointer));
		}
		if (((Collision*)c->GetFixtureB()->GetBody()->GetUserData().pointer)->collisionFunc != nullptr) {
			((Collision*)c->GetFixtureB()->GetBody()->GetUserData().pointer)->collisionFunc(((Collision*)c->GetFixtureA()->GetBody()->GetUserData().pointer));
		}
	}

}

void CollisionSystem::RemoveFromSystem(UI32 id, GameObject* obj) {
	SystemProgram::RemoveFromSystem(id, obj);
	Collision* collision = (Collision*) obj->GetComponent("Collision");
	if (collision != nullptr) {
		if (collision->body != nullptr) {
			world.DestroyBody(collision->body);
		}
	}
}

void CollisionSystem::SetGravity(Vec2f gravity) {
	world.SetGravity(Vec2fToB2Vec2(gravity));
}

Vec2f CollisionSystem::GetGravity() {
	return b2Vec2ToVec2f(world.GetGravity());
}