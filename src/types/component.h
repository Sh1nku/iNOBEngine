#pragma once
#include "enginetypes.h"
#include <nlohmann/json.hpp>
#include <unordered_map>

class Component;
class GameObject;

typedef std::unordered_map<std::string, Component*(*)(nlohmann::json json)> mapType;

class Component
{
public:
	friend class GameObject;
	Component(GameObject *parent = nullptr);
	virtual ~Component();

	GameObject *GetParent();
	virtual UI32 GetBitcode() = 0;

	static Component* GetComponentFromJson(nlohmann::json &json);
	static void AddBitcode(std::string name);
	static UI32 GetBitcode(std::string type);
protected:
	GameObject *mParent;
	void SetParent(GameObject* parent);
};

template<typename T> Component* CreateComponent(nlohmann::json json) {
	T *t = new T();
	from_json(json, *t);
	return t;
}


extern std::unordered_map< std::string, UI32> bitcodes;
extern mapType jsonComponentList;