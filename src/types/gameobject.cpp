#include "gameobject.h"
#include <iostream>
#include "types\components\transform.h"

UI32 globalID = 1;
std::vector<UI32> globalPoolIDS;

GameObject::GameObject(GameObject* parent) : mID(0), mName(""), mNamed(false), mParent(parent)
{
	if (parent != nullptr) {
		this->mParent->mChildren.emplace_back(this);
	}
	transform = this->AddComponent<Transform>();
}

GameObject* GameObject::Create() {
	return new GameObject();
}

GameObject::~GameObject() 
{
	for (Component* v : mComponents) {
		delete v;
	}
	if (mID == 0) {
		for (GameObject* obj : mChildren) {
			delete obj;
		}
		mChildren.clear();
	}
	}

UI32 GameObject::GetID() {
	return mID;
}

std::string GameObject::GetName() {
	return mName;
}