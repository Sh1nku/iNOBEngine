#include "transform.h"
#include "../gameobject.h"
#include "../component.h"

Component::TYPE Transform::GetBitcode() {
	return Component::TYPE::TRANSFORM;
}

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

b2Vec2 Transform::GetWorldPosition() const{
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

void to_json(nlohmann::json& j, const Transform& t) {
	b2Vec2 position = t.GetLocalPosition();
	j = nlohmann::json{ {"name", "Transform"}, {"position", std::vector<float>{position.x, position.y} } };
}

void from_json(const nlohmann::json& j, Transform& t) {
	std::vector<float> positionVector;
	j.at("position").get_to(positionVector);
	t.SetLocalPosition(&b2Vec2(positionVector[0], positionVector[1]));
}