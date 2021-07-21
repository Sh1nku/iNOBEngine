#pragma once
#include "enginetypes.h"
#include <nlohmann/json.hpp>
#include <unordered_map>

class Component;
class GameObject;

typedef std::unordered_map<std::string, Component*(*)(nlohmann::json json)> mapType;
extern std::unordered_map< std::string, UI32> bitcodes;
extern mapType jsonComponentList;

template<typename T> Component* CreateComponent(nlohmann::json json) {
	T* t = new T();
	from_json(json, *t);
	return t;
}

template<typename T> void AddComponentToList(std::string name) {
	Component::AddBitcode(name);
	Component::AddComponent(name, &CreateComponent<T>);

}


class Component
{
public:
	friend class GameObject;
	template<typename> friend void AddComponentToList(std::string name);
	Component(GameObject *parent = nullptr);
	virtual ~Component();

	GameObject *GetParent();
	virtual UI32 GetBitcode() = 0;

	static Component* GetComponentFromJson(nlohmann::json &json);
	static UI32 GetBitcode(std::string type);
protected:
	GameObject *mParent;
	void SetParent(GameObject* parent);
	virtual Component* Clone(GameObject* parent = nullptr) = 0;
	static void AddBitcode(std::string name);
	static void AddComponent(const std::string& name, Component* (*function)(nlohmann::json json));
};