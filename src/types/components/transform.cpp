#include "transform.h"
#include "../gameobject.h"
#include "../component.h"
#include "collision.h"

Component* Transform::Clone(GameObject* parent) {
	Transform* component = new Transform();
	component->mParent = parent;
	component->mWorldPosition = mWorldPosition;
	component->mWorldRotation = mWorldRotation;
	return component;
}

UI32 Transform::GetBitcode() {
	static UI32 bitcode = Component::GetBitcode("Transform");
	return bitcode;
}

const auto x = [] {
	AddComponentToList<Transform>("Transform");
	return true;
}();

Vec3f Transform::GetLocalPosition() const{
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

const Vec2f& Transform::GetScreenPosition() const
{
	return mScreenPosition;
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

Vec3f Transform::GetWorldPosition() const {
	return mWorldPosition;
}

void Transform::SetLocalPosition(const Vec3f& position) {
	auto oldPos = mWorldPosition;
	if (mParent != nullptr) {
		if (mParent->mParent != nullptr) {
			mWorldPosition = mParent->mParent->transform->mWorldPosition + position;
		}
		else {
			mWorldPosition = position;
		}
	}
	else {
		mWorldPosition = position;
	}
	if (mParent != nullptr) {
		for (GameObject* go : mParent->mChildren) {
			go->transform->UpdatePosition(&oldPos);
		}
	}
}

void Transform::SetScreenPosition(const Vec2f& position) {
	this->mScreenPosition.x = position.x;
	this->mScreenPosition.y = position.y;
}

void Transform::SetWorldPosition(const Vec3f& position) {
	auto oldPos = mWorldPosition;
	mWorldPosition = position;
	if (mParent != nullptr) {
		for (GameObject* go : mParent->mChildren) {
			go->transform->UpdatePosition(&oldPos);
		}
	}
}

void Transform::SetWorldRotation(float rotation) {
	mWorldRotation = rotation;
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

float Transform::GetScale() const
{
	return mScale;
}

void Transform::UpdatePosition(Vec3f* oldPos) {
	auto oldPos2 = mWorldPosition;
	mWorldPosition = mParent->mParent->transform->mWorldPosition - (*oldPos - mWorldPosition);
	for (GameObject* go : mParent->mChildren) {
		go->transform->UpdatePosition(&oldPos2);
	}
}

void to_json(nlohmann::json& j, const Transform& t) {
	auto position = t.GetLocalPosition();
	j = nlohmann::json{ {"name", "Transform"}, {"position", std::vector<float>{position.x, position.y, position.z} } };
}

void from_json(const nlohmann::json& j, Transform& t) {
	std::vector<float> positionVector;
	j.at("position").get_to(positionVector);
	if (positionVector.size() == 2) {
		positionVector.emplace_back(0);
	}
	t.SetLocalPosition(Vec3f(positionVector[0], positionVector[1], positionVector[2]));
	return;
}