#include "gameobject.h"
#include "component.h"
#include <iostream>
#include "types/components/transform.h"

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

Component* GameObject::AddComponent(Component* component) {
	if (std::type_index(typeid(*component)) == std::type_index(typeid(Transform))) {
		mComponents.erase(mComponents.begin());
		delete transform;
		transform = (Transform*) component;
		mComponents.push_back(component);
	}
	else {
		mComponents.push_back(component);
		return component;
	}
}

GameObject* GameObject::LoadFromFile(std::string contents, GameObject* parent) {
	nlohmann::json jsonAll = nlohmann::json::parse(contents);
	nlohmann::json go = jsonAll.at("GameObject");
	GameObject* gameObject = new GameObject();
	try {
		std::string name = go.at("name");
		gameObject->mName = name;
		gameObject->mNamed = true;
	}
	catch(std::exception& ex) {
		std::cout << "Name not found" << std::endl;
	}
	nlohmann::json components = go.at("components");
	for (nlohmann::json componentJson : components) {
		Component* component = jsonComponentList[componentJson.at("name")](componentJson);
		component->SetParent(gameObject);
		gameObject->AddComponent(component);

	}
	return gameObject;
};