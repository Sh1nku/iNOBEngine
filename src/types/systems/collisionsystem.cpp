#include "collisionsystem.h"
#include "../components/collision.h"
#include "../gameobject.h"
#include "../../manager.h"

CollisionSystem::CollisionSystem(b2Vec2 gravity) : world(gravity) {
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
			collision->body->SetActive(true);
			if (collision->body->GetPosition() != transform->GetWorldPosition() || collision->body->GetAngle() != transform->GetWorldRotation()) {
				collision->body->SetTransform(transform->GetWorldPosition(), transform->GetWorldRotation());
			}
		}
		else {
			Collision* collision = (Collision*)entry.second->at(Component::GetBitcode("Collision"));
			if (collision->body != nullptr) {
				collision->body->SetActive(false);
			}
		}
	}
	world.Step(dt, 8, 3);
	for (auto& entry : *GetEntries(Component::GetBitcode("Collision") | Component::GetBitcode("Transform"))) {
		if (entry.first->active) {
			Collision* collision = (Collision*)entry.second->at(Component::GetBitcode("Collision"));
			Transform* transform = (Transform*)entry.second->at(Component::GetBitcode("Transform"));
			if (collision->body != nullptr) {
				if (collision->body->GetPosition() != transform->GetWorldPosition() || collision->body->GetAngle() != transform->GetWorldRotation()) {
					transform->SetWorldPosition((b2Vec2*)&collision->body->GetPosition()); 
					transform->SetWorldRotation(collision->body->GetAngle());
				}
			}
		}
	}
	for (b2Contact* c = world.GetContactList(); c; c = c->GetNext()) {
		if (((Collision*)c->GetFixtureA()->GetBody()->GetUserData())->collisionFunc != nullptr) {
			((Collision*)c->GetFixtureA()->GetBody()->GetUserData())->collisionFunc(((Collision*)c->GetFixtureB()->GetBody()->GetUserData()));
		}
		if (((Collision*)c->GetFixtureB()->GetBody()->GetUserData())->collisionFunc != nullptr) {
			((Collision*)c->GetFixtureB()->GetBody()->GetUserData())->collisionFunc(((Collision*)c->GetFixtureA()->GetBody()->GetUserData()));
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

void CollisionSystem::SetGravity(b2Vec2 gravity) {
	world.SetGravity(gravity);
}

b2Vec2 CollisionSystem::GetGravity() {
	return world.GetGravity();
}