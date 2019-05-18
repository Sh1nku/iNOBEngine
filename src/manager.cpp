#include "manager.h"
#include "types/gameobject.h"
#include <typeindex>
#include <vector>
#include "types/systemprogram.h"
#include <algorithm>
#include "types/components/transform.h"
#include "Box2D/Box2D.h"

Manager* Manager::manager = nullptr;

Manager::Manager() {

}

Manager::~Manager() {
	for (std::map<UI32, GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
	{
		delete it->second;
	}
	mGameObjects.clear();
	for (std::vector< SystemProgram* >::iterator it = mSystems.begin(); it != mSystems.end(); ++it) {
		delete (*it);
	}
	mSystems.clear();
	manager = nullptr;
}

GameObject* Manager::AddGameObject(GameObject *obj) {
	if (globalPoolIDS.size() == 0) {
		obj->mID = globalID++;
	}
	else {
		obj->mID = globalPoolIDS.back();
		globalPoolIDS.pop_back();
	}
	mGameObjects.insert({ obj->GetID(), obj });
	for (auto& system : mSystems) {
		system->AddToSystem(obj);
	}
	for (GameObject* obj2 : (*(obj)).mChildren) {
		AddGameObject(obj2);
	}
	return obj;
}

Manager *Manager::GetInstance(){
	if (manager == nullptr) {
		manager = new Manager();
	}
	return manager;
}

GameObject* Manager::Instantiate(GameObject* obj, std::string name, b2Vec2* pos) {
	AddGameObject(obj);
	if (obj->mName != "") {
		obj->mNamed = true;
		namedObjects.emplace_back(obj);
	}
	else {
		obj->mName = name;
		if (name != "") {
			obj->mNamed = true;
			namedObjects.emplace_back(obj);
		}
	}
	if (pos != nullptr) {
		obj->transform->SetLocalPosition(pos);
	}
	return obj;
}

void Manager::Destroy(GameObject* obj) {
	auto& key = objectsToBeDeleted.find(obj);
	if (key == objectsToBeDeleted.end()) {
		objectsToBeDeleted.emplace(obj);
	}
}

SystemProgram* Manager::AddSystem(SystemProgram* system) {
	mSystems.emplace_back(system);
	for (auto& obj : mGameObjects) {
		system->AddToSystem(obj.second);
	}
	return system;
}

GameObject* Manager::GetGameObjectByID(UI32 id) {
	std::map<UI32, GameObject*>::iterator it;
	it = mGameObjects.find(id);
	if (it != mGameObjects.end()) {
		return it->second;
	}
	else {
		return nullptr;
	}
}

GameObject* Manager::GetGameObjectByName(std::string name) {
	std::vector<GameObject*>::iterator it;
	for (it = namedObjects.begin(); it != namedObjects.end(); ++it) {
		if ((*it)->mName == name) {
			return (*it);
		}
	}
	return nullptr;
}

void Manager::Update(float dt) {
	for (SystemProgram* system : mSystems) {
		if (system->active) {
			system->Update(dt);
		}
	}
	for (GameObject* obj : objectsToBeDeleted) {
		RemoveGameObject(obj);
	}
	objectsToBeDeleted.clear();
}

void Manager::RemoveGameObject(GameObject* obj) {
	std::set<GameObject*>* set = &objectsToBeDeleted;
	for (GameObject* child : obj->mChildren) {
		auto& childIt = objectsToBeDeleted.find(child);
		if (childIt != objectsToBeDeleted.end()) {
			objectsToBeDeleted.erase(childIt);
		}
		RemoveGameObject(child);
	}
	if (obj->GetID() != 0) {
		globalPoolIDS.push_back(obj->mID);
		mGameObjects.erase(obj->GetID());

		if (obj->mNamed) {
			namedObjects.erase(std::remove(namedObjects.begin(), namedObjects.end(), obj), namedObjects.end());
		}
		for (auto& system : mSystems) {
			system->RemoveFromSystem(obj->GetID(), obj);
		}
	}
	if (obj->mParent != nullptr) {
		obj->mParent->mChildren.erase(std::remove(obj->mParent->mChildren.begin(), obj->mParent->mChildren.end(), obj), obj->mParent->mChildren.end());
	}
	delete obj;
}