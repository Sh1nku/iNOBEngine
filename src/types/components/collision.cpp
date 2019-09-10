#include "collision.h"
#include "../jsontypes.h"
#include "../gameobject.h"
#include "../component.h"
#include <iostream>

Collision::Collision(GameObject *parent) : Component(parent), body(nullptr), collisionFunc(nullptr), mScale(1) {
	bodyDef.userData = this;
}

Collision::~Collision() {
	for (auto& fixture : fixtures) {
		delete fixture.shape;
	}
}

Component* Collision::Clone(GameObject* parent) {
	Collision* collision = new Collision();
	collision->mParent = parent;
	collision->bodyDef = bodyDef;
	for (int i = 0; i < fixtures.size(); i++) {
		b2FixtureDef def(fixtures.at(i));
		def.shape = cloneB2Shape((b2Shape*)def.shape);
		collision->fixtures.emplace_back(def);
	}
	collision->mScale = mScale;
	collision->bodyDef.userData = collision;
	return collision;
}

UI32 Collision::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Collision");
	return bitcode;
}

const auto x = [&] {
	AddComponentToList<Collision>("Collision");
	return true;
}();

void Collision::SetLinearVelocity(b2Vec2 vel) {
	if (body != nullptr) {
		body->SetLinearVelocity(vel);
	}
	else {
		bodyDef.linearVelocity.Set(vel.x, vel.y);
	}
}

void Collision::SetAngularVelocity(float vel)
{
	if (body != nullptr) {
		body->SetAngularVelocity(vel);
	}
	else {
		bodyDef.angularVelocity = vel;
	}
}

void Collision::SetCollisionFunc(std::function<void(Collision*)> func)
{
	collisionFunc = func;
}

b2Shape * Collision::cloneB2Shape(b2Shape * shape)
{
	if (shape->GetType() == b2Shape::e_circle) {
		b2CircleShape* circle = new b2CircleShape(*(b2CircleShape*)shape);
		return circle;
	}
	else if (shape->GetType() == b2Shape::e_polygon){
		b2PolygonShape* polygon = new b2PolygonShape(*(b2PolygonShape*)shape);
		std::copy(std::begin(((b2PolygonShape*)shape)->m_vertices), std::end(((b2PolygonShape*)shape)->m_vertices), std::begin(polygon->m_vertices));
		return polygon;
	}
	else {
		throw new std::exception("The collision structure is not supported");
	}
}

void Collision::SetScale(float scale) {
	if (body != nullptr) {
		bodyDef.linearVelocity = body->GetLinearVelocity();
		bodyDef.angularVelocity = body->GetAngularVelocity();
		body->GetWorld()->DestroyBody(body);
		body = nullptr;
	}
	for (auto& fixture : fixtures) {
		if (fixture.shape->GetType() == b2Shape::e_polygon) {
			for (int i = 0; i < b2_maxPolygonVertices; i++) {
				//Return to scale 1.0, then apply new scale
				((b2PolygonShape*)fixture.shape)->m_vertices[i].x /= mScale;
				((b2PolygonShape*)fixture.shape)->m_vertices[i].y /= mScale;
				((b2PolygonShape*)fixture.shape)->m_vertices[i].x *= scale;
				((b2PolygonShape*)fixture.shape)->m_vertices[i].y *= scale;
			}
		}
		else if (fixture.shape->GetType() == b2Shape::e_circle) {
			((b2CircleShape*)fixture.shape)->m_radius /= mScale;
			((b2CircleShape*)fixture.shape)->m_radius *= scale;
		}
		else {
			throw new std::exception("Fixture shape is not defined");
		}
	}
	mScale = scale;
}

void to_json(nlohmann::json& j, const Collision& t) {

}

void from_json(const nlohmann::json& j, Collision& t) {
	auto& bodyType = j.find("type");
	if (bodyType != j.end()) {
		if (bodyType.value() == "dynamic") {
			t.bodyDef.type = b2_dynamicBody;
		}
		else if (bodyType.value() == "kinematic") {
			t.bodyDef.type = b2_kinematicBody;
		}
		else {
			t.bodyDef.type = b2_staticBody;
		}
	}
	else {
		t.bodyDef.type = b2_staticBody;
	}
	auto& bullet = j.find("bullet");
	if (bullet != j.end()) {
		t.bodyDef.bullet = bullet.value();
	}
	auto& preventRotation = j.find("fixedrotation");
	if (preventRotation != j.end()) {
		t.bodyDef.fixedRotation =	preventRotation.value();
	}
	std::vector<nlohmann::json> defs;
	j.at("bodydef").get_to(defs);
	for (auto& def : defs) {
		b2FixtureDef fixtureDef;
		if (def.at("type") == "polygon") {
			std::vector<b2Vec2> polygonCoords;
			def.at("coords").get_to(polygonCoords);
			///TODO Memory leak
			b2PolygonShape *shape = new b2PolygonShape();
			shape->Set(polygonCoords.data(), polygonCoords.size());
			fixtureDef.shape = shape;
		}
		else if (def.at("type") == "circle") {
			float radius = def.at("radius");
			///TODO Memory leak
			b2CircleShape *circle = new b2CircleShape();
			circle->m_radius = radius;
			fixtureDef.shape = circle;
		}
		auto& density = def.find("density");
		if (density != def.end()) {
			fixtureDef.density = def.at("density");
		}
		else {
			fixtureDef.density = 1.0;
		}
		auto& categoryBits = def.find("categorybits");
		if (categoryBits != def.end()) {
			fixtureDef.filter.categoryBits = stringToBin(categoryBits.value());
		}
		auto& maskBits = def.find("maskbits");
		if (maskBits != def.end()) {
			fixtureDef.filter.maskBits = stringToBin(maskBits.value());
		}
		t.fixtures.emplace_back(fixtureDef);
	}
	t.bodyDef.userData = &t;
	t.fixtures;
}

UI16 stringToBin(std::string str) {
	UI16 ret = 0;
	for (int i = 0; i < str.size(); i++) {
		if (((int)str.at(i) - 48) == 1) {
			ret += 1 << (str.size() - (i+1));
		}
	}
	return ret;
}