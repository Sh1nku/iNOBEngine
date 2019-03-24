#pragma once
#include "enginetypes.h"
#include <json.hpp>
#include <unordered_map>

class Component;
class GameObject;

typedef std::unordered_map<std::string, Component*(*)(nlohmann::json json)> mapType;

class Component
{
public:
	friend class GameObject;
	enum TYPE{ TRANSFORM = 1 , TEST_COMPONENT = 1 << 1, CAMERA = 1 << 3, ANIMATION = 1 << 4};
	Component(GameObject *parent = nullptr);
	virtual ~Component();

	GameObject *GetParent();

	virtual TYPE GetBitcode() = 0;

	static Component* GetComponentFromJson(nlohmann::json &json);

protected:
	GameObject *mParent;
	void SetParent(GameObject* parent);
};

template<typename T> Component* CreateComponent(nlohmann::json json) {
	T *t = new T();
	from_json(json, *t);
	return t;
}
extern mapType jsonComponentList;