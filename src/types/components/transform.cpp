#include "transform.h"
#include "../gameobject.h"
#include "../component.h"
#include "collision.h"

Component* Transform::Clone(GameObject* parent) {
	Transform* component = new Transform();
	component->mParent = parent;
	component->mWorldPosition = mWorldPosition;
	component->mWorldRotation = mWorldRotation;
	component->zCoord = zCoord;
	return component;
}

UI32 Transform::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Transform");
	return bitcode;
}

const auto x = [&] {
	AddComponentToList<Transform>("Transform");
	return true;
}();

b2Vec2 Transform::GetLocalPosition() const{
	if (mParent != nullptr) {
		if (mParent->mParent != nullptr) {
			return mParent->mParent->transform->mWorldPosition - mWorldPosition;
		}
		return mWorldPosition;
	}
	else {
		return mWorldPosition;
	}
}

float Transform::GetWorldRotation() const{
	return mWorldRotation;
}

float Transform::GetLocalRotation() const {
	if (mParent != nullptr) {
		if (mParent->mParent != nullptr) {
			return mParent->mParent->transform->mWorldRotation - mWorldRotation;
		}
		return mWorldRotation;
	}
	else {
		return mWorldRotation;
	}
}

b2Vec2 Transform::GetWorldPosition() const {
	return mWorldPosition;
}

void Transform::SetLocalPosition(b2Vec2* position) {
	if (mParent != nullptr) {
		if (mParent->mParent != nullptr) {
			mWorldPosition = mParent->mParent->transform->mWorldPosition + *position;
		}
		else {
			mWorldPosition = *position;
		}
	}
	else {
		mWorldPosition = *position;
	}
	if (mParent != nullptr) {
		for (GameObject* go : mParent->mChildren) {
			go->transform->SetWorldPosition(&(go->transform->GetLocalPosition()));
		}
	}
}

void Transform::SetWorldPosition(b2Vec2* position) {
	mWorldPosition = *position;
	if (mParent != nullptr) {
		for (GameObject* go : mParent->mChildren) {
			go->transform->SetWorldPosition(&(go->transform->GetLocalPosition()));
		}
	}
}

void Transform::SetWorldRotation(float rotation) {
	mWorldRotation = rotation;
}

void Transform::SetZCoord(float zCoord) {
	this->zCoord = zCoord;
}

void Transform::SetScale(float scale)
{
	if (mParent != nullptr) {
		Collision* collision = (Collision*)mParent->GetComponent("Collision");
		if (collision != nullptr) {
			collision->SetScale(scale);
		}
	}
	mScale = scale;
}

float Transform::GetZCoord() const{
	return this->zCoord;
}

float Transform::GetScale() const
{
	return mScale;
}

void to_json(nlohmann::json& j, const Transform& t) {
	b2Vec2 position = t.GetLocalPosition();
	j = nlohmann::json{ {"name", "Transform"}, {"position", std::vector<float>{position.x, position.y} }, {"z", t.GetZCoord()} };
}

void from_json(const nlohmann::json& j, Transform& t) {
	std::vector<float> positionVector;
	j.at("position").get_to(positionVector);
	t.SetLocalPosition(&b2Vec2(positionVector[0], positionVector[1]));
	auto& it = j.find("z");
	if (it != j.end()) {
		t.SetZCoord(it.value());
	}
}