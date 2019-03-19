#include "transform.h"
#include "../gameobject.h"
#include "../component.h"

Component::TYPE Transform::GetBitcode() {
	return Component::TYPE::TRANSFORM;
}

b2Vec2 Transform::GetLocalPosition() {
	if (mParent->mParent != nullptr) {
		return mParent->mParent->transform->mWorldPosition - mWorldPosition;
	}
	else {
		return mWorldPosition;
	}
}

b2Vec2 Transform::GetWorldPosition() {
	return mWorldPosition;
}

void Transform::SetLocalPosition(b2Vec2* position) {
	if (mParent->mParent != nullptr) {
		mWorldPosition = mParent->mParent->transform->mWorldPosition + *position;
	}
	else {
		mWorldPosition = *position;
	}
	for (GameObject* go : mParent->mChildren) {
		go->transform->SetWorldPosition(&(go->transform->GetLocalPosition()));
	}
}

void Transform::SetWorldPosition(b2Vec2* position) {
	mWorldPosition = *position;
	for (GameObject* go : mParent->mChildren) {
		go->transform->SetWorldPosition(&(go->transform->GetLocalPosition()));
	}
}

void to_json(nlohmann::json& j, const Transform& t) {
	j = nlohmann::json{ { "position", 32 } };
}

void from_json(const nlohmann::json& j, Transform& t) {
	int i;
	j.at("position").get_to(i);
}