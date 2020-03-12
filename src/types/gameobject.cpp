#include "gameobject.h"
#include "component.h"
#include <iostream>
#include "components/transform.h"
#include "script.h"
#include "../manager.h"

UI32 globalID = 1;
std::vector<UI32> globalPoolIDS;

GameObject::GameObject(GameObject* parent) : mID(0), mName(""), mNamed(false), mParent(parent), active(true)
{
	if (parent != nullptr) {
		this->mParent->mChildren.emplace_back(this);
	}
	transform = this->AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& old) {
	mName = old.mName.c_str();
	mNamed = old.mNamed;
	mID = 0;
	mParent = old.mParent;
	active = old.active;
	for (auto comp : old.mComponents) {
		mComponents.emplace(comp.first, comp.second->Clone(this));
	}
	transform = (Transform*) GetComponent("Transform");
	for (auto childObj : old.mChildren) {
		GameObject* newObj = new GameObject(childObj);
		newObj->mParent = this;
		mChildren.emplace_back(newObj);
	}
}

GameObject* GameObject::Create() {
	return new GameObject();
}

GameObject::~GameObject() 
{
	for (auto &v : mComponents) {
		delete v.second;
	}
	mComponents.clear();
	if (mID == 0) {
		for (GameObject* obj : mChildren) {
			delete obj;
		}
		mChildren.clear();
	}
	for (auto& it : subscribedEvents) {
		Manager::GetInstance()->eventManager.Unsubscribe(it);
	}
	subscribedEvents.clear();
}

UI32 GameObject::GetID() {
	return mID;
}

UI32 GameObject::GetComponentEnum() {
	UI32 compEnum = 0;
	for (auto& entry : mComponents) {
		compEnum |= entry.second->GetBitcode();
	}
	return compEnum;
}

std::string GameObject::GetName() {
	return mName;
}

Component* GameObject::AddComponent(Component* component) {
	if (std::type_index(typeid(*component)) == std::type_index(typeid(Transform))) {
		if (mComponents.size() > 0) {
			for (auto& entry : mComponents) {
				if (entry.first == bitcodes.at("Transform")) {
					delete entry.second;
					entry.second = component;
				}
			}
		}
		transform = (Transform*) component;
		mComponents.emplace( component->GetBitcode(), component );
		return component;
	}
	else {
		mComponents.emplace(component->GetBitcode(), component);
		return component;
	}
}

GameObject* GameObject::LoadFromFile(std::string contents, GameObject* parent) {
	nlohmann::json jsonAll = nlohmann::json::parse(contents);
	nlohmann::json go = jsonAll.at("GameObject");
	GameObject* gameObject = new GameObject(parent);
	try {
		std::string name = go.at("name");
		gameObject->mName = name;
		gameObject->mNamed = true;
	}
	catch(std::exception) {
		std::cout << "Name not found" << std::endl;
	}
	auto& isActive = go.find("active");
	if (isActive != go.end()) {
		gameObject->active = isActive.value();
	}
	auto& retainOnLoad = go.find("retainOnLoad");
	if (retainOnLoad != go.end()) {
		gameObject->retainOnLoad = retainOnLoad.value();
	}
	nlohmann::json components = go.at("components");
	for (nlohmann::json componentJson : components) {
		Component* component = jsonComponentList.at(componentJson.at("name"))(componentJson);
		component->SetParent(gameObject);
		gameObject->AddComponent(component);

		//Add parent's position to child
		if (component->GetBitcode() == bitcodes.at("Transform") && parent != nullptr) {
			((Transform*)component)->SetWorldPosition( &(((Transform*)component)->GetWorldPosition() +
				parent->transform->GetWorldPosition()));
		}

	}
	auto& children = go.find("children");
	if (children != go.end()) {
		for (nlohmann::json childJson : children.value()) {
			GameObject* child = LoadFromFile(childJson.dump(), gameObject);
		}
	}
	return gameObject;
};

Component* GameObject::GetComponent(std::string type) {
	try {
		return mComponents.at(bitcodes.at(type));
	}
	catch (std::exception) {
		return nullptr;
	}
}

void GameObject::Subscribe(std::string ev, std::function<void(void*)> func) {
	subscribedEvents.push_back(Manager::GetInstance()->eventManager.Subscribe(ev, func));
}