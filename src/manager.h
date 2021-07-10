#pragma once

#include <vector>
#include <map>
#include <set>
#include "types/enginetypes.h"
#include "box2d/box2d.h"
#include "types/vectors.h"
#include "eventmanager.h"
#include <functional>
#include <typeindex>

class GameObject;
class SystemProgram;
class Resources;
class EventManager;

class Manager
{
public:
	friend class EventManager;
	friend class Resources;
	friend class SystemProgram;
	friend class RenderSystem;
	virtual ~Manager();
	static Manager* GetInstance();
	static bool IsStarted();
	SystemProgram* AddSystem(SystemProgram *system);
	GameObject* Instantiate(GameObject* obj, std::string name = "", Vec3f* pos = nullptr);
	void LoadScene(const std::string& name);
	void Destroy(GameObject* obj);
	void Update(float dt);

	template <class T>
	T* GetSystem() {
		for (SystemProgram* v : mSystems) {
			if (std::type_index(typeid(T)) == std::type_index(typeid(*v))) {
				return ((T*) v);
			}
			else {
			}
		}
		return nullptr;
	}
	GameObject* GetGameObjectByName(std::string name);
	GameObject* GetGameObjectByID(UI32 id);
	std::map<UI32, GameObject*>& GetGameObjects();

	void Subscribe(EventManager* ptr, std::string ev, EventManager* ref, std::function<void(void*)> func);
	void FireEvent(EventManager* ptr, std::string ev, void* data);

protected:
	void Unsubscribe(EventManager* ptr, std::string ev, EventManager* obj);
	void RemoveFromEvent(EventManager* ev);


private:
	Manager();
	GameObject* AddGameObject(GameObject *gameObject);
	void RemoveGameObject(GameObject* gameObject);

	std::map<UI32, GameObject*> mGameObjects;
	std::set<GameObject*> objectsToBeDeleted;
	std::vector<GameObject*> namedObjects;
	std::vector<SystemProgram*> mSystems;
	std::unordered_map < EventManager*, std::unordered_map < std::string, std::unordered_map<EventManager*, std::function<void(void*)>>>> mEvents;

	void LoadNewScene();
	std::string sceneToLoad = "";
	void RemoveChildrenIfDontRetain(GameObject* obj);

	static Manager* manager;
};