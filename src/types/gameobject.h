#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <memory>
#include "../types/component.h"
#include <typeindex>
#include "enginetypes.h"

extern UI32 globalID;
extern std::vector<UI32> globalPoolIDS;

struct b2Vec2;
class Transform;

class GameObject {
	friend class Manager;
	friend class Transform;
	public:
		GameObject(GameObject* parent = nullptr);
		~GameObject();

		template <class T>
		T *GetComponent() {
			for (Component* v : mComponents) {
				if (std::type_index(typeid(T)) == std::type_index(typeid(*v))) {
					return ((T*)v);
				}
				else {
				}
			}
			return nullptr;
		}

		template <class T>
		T *AddComponent() {
			T *component = new T(this);
			mComponents.push_back(component);
			return component;
		}

		GameObject* GetParent() { return mParent; }

		UI32 GetID();
		std::string GetName();
		static GameObject* Create();
		Transform *transform;
	private:
		std::vector<Component*> mComponents;
		std::vector<GameObject*> mChildren;
		std::string mName;
		bool mNamed;
		UI32 mID;
		GameObject* mParent;
};

#endif