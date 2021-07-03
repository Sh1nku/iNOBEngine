#include "manager.h"
#include "io/resources.h"
#include "types/gameobject.h"
#include <typeindex>
#include <vector>
#include "types/systemprogram.h"
#include <algorithm>
#include "types/components/transform.h"
#include "box2d/box2d.h"
#include "eventmanager.h"

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
	if (obj->mName != "") {
		obj->mNamed = true;
		namedObjects.emplace_back(obj);
	}
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

GameObject* Manager::Instantiate(GameObject* obj, std::string name, Vec3f* pos) {
	AddGameObject(obj);
	if (name != "") {
		obj->mName = name;
		obj->mNamed = true;
		std::remove_if(namedObjects.begin(), namedObjects.end(), [&](GameObject* obj2) {return obj2 == obj; });
		namedObjects.emplace_back(obj);
	}
	if (pos != nullptr) {
		obj->transform->SetLocalPosition(*pos);
	}
	return obj;
}

void Manager::LoadScene(const std::string& name) {
	sceneToLoad = name;
}

void Manager::RemoveChildrenIfDontRetain(GameObject* obj) {
	if (!obj->retainOnLoad) {
		auto tempChildren = obj->mChildren;
		for (auto& child : tempChildren) {
			RemoveChildrenIfDontRetain(child);
		}
		obj->mChildren.clear();
		RemoveGameObject(obj);
	}
	else {
		obj->mParent = nullptr;
	}
}

void Manager::LoadNewScene() {
	Resources::LoadScene(sceneToLoad);
	sceneToLoad = "";
}

void Manager::Destroy(GameObject* obj) {
	const auto& key = objectsToBeDeleted.find(obj);
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

	if (sceneToLoad != "") {
		LoadNewScene();
	}
}

void Manager::RemoveGameObject(GameObject* obj) {
	std::set<GameObject*>* set = &objectsToBeDeleted;
	for (GameObject* child : obj->mChildren) {
		const auto& childIt = objectsToBeDeleted.find(child);
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

std::map<UI32, GameObject*>& Manager::GetGameObjects(){
	return mGameObjects;
}

void Manager::FireEvent(EventManager* ptr, std::string ev, void* data) {
	const auto& i = mEvents.find(ptr);
	if (i != mEvents.end()) {
		const auto& j = i->second.find(ev);
		if (j != i->second.end()) {
			for (auto& func : j->second) {
				std::bind(func.second, data)();
			}
		}
	}
}

void Manager::Subscribe(EventManager* ptr, std::string ev, EventManager* ref, std::function<void(void*)> func) {
	auto i = mEvents.find(ptr);
	if (i == mEvents.end()) {
		mEvents.emplace(ptr, std::unordered_map < std::string, std::unordered_map<EventManager*, std::function<void(void*)>>>());
		i = mEvents.find(ptr);
	}
	auto j = i->second.find(ev);
	if (j == i->second.end()) {
		i->second.emplace(ev, std::unordered_map < EventManager*, std::function<void(void*)>>());
		j = i->second.find(ev);
	}
	j->second.emplace(ref, func);
}

void Manager::Unsubscribe(EventManager* ptr, std::string ev, EventManager* obj) {
	const auto& i = mEvents.find(ptr);
	if (i != mEvents.end()) {
		const auto& j = i->second.find(ev);
		if (j != i->second.end()) {
			const auto& k = j->second.find(obj);
			if (k != j->second.end()) {
				j->second.erase(k);
			}
		}
	}
}

void Manager::RemoveFromEvent(EventManager* ev) {
	const auto& i = mEvents.find(ev);
	if (i != mEvents.end()) {
		mEvents.erase(i);
	}
}