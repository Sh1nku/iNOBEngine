#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <memory>
#include "../types/component.h"
#include "../types/components/transform.h"
#include "../types/components/input.h"
#include <typeindex>
#include "enginetypes.h"

extern UI32 globalID;
extern std::vector<UI32> globalPoolIDS;

struct b2Vec2;
class Transform;
class SystemProgram;
class Script;

class GameObject {
	friend class Manager;
	friend class Transform;
	friend class SystemProgram;
	public:
		GameObject(GameObject* parent = nullptr);
		GameObject(const GameObject&);
		~GameObject();

		template <class T>
		T *GetComponent() {
			for (auto& v : mComponents) {
				if (std::type_index(typeid(T)) == std::type_index(typeid(*v.second))) {
					return ((T*)v.second);
				}
				
			}
			return nullptr;
		}

		template <class T>
		T *AddComponent() {
			T *component = new T(this);
			AddComponent(component);
			return component;
		}
		Component* GetComponent(std::string type);

		Component* AddComponent(Component* component);

		GameObject* GetParent() { return mParent; }
		UI32 GetComponentEnum();
		UI32 GetID();
		std::string GetName();


		static GameObject* Create();
		static GameObject* LoadFromFile(std::string fileContents, GameObject* parent = nullptr);

		bool active = true;
		Transform *transform;
	private:
		std::unordered_map<UI32 ,Component*> mComponents;
		std::vector<Script> mScripts;
		std::vector<GameObject*> mChildren;
		std::string mName;
		bool mNamed;
		UI32 mID;
		GameObject* mParent;
};

#endif