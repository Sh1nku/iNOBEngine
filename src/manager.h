#pragma once

#include <vector>
#include <map>
#include "types/enginetypes.h"
#include "Box2D/Box2D.h"

class GameObject;
class SystemProgram;

class Manager
{
public:
	virtual ~Manager();
	static Manager* GetInstance();
	SystemProgram* AddSystem(SystemProgram *system);
	GameObject* Instantiate(GameObject* obj, std::string name = "", b2Vec2* pos = nullptr);
	void Destroy(GameObject* obj);
	
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

private:
	Manager();
	GameObject* AddGameObject(GameObject *gameObject);

	std::map<UI32, GameObject*> mGameObjects;
	std::vector<GameObject*> namedObjects;
	std::vector<SystemProgram*> mSystems;

	static Manager* manager;
};