#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "enginetypes.h"

class GameObject;
class Component;

typedef std::unordered_map<UI32, Component*> component_map;
typedef std::unordered_map<GameObject*, std::unique_ptr<component_map>> gameObject_map;


class SystemProgram
{
public:
	SystemProgram();
	virtual ~SystemProgram();
	bool active = true;
	virtual void Update(float dt);
	void AddToSystem(GameObject* obj);
	virtual void RemoveFromSystem(UI32 id, GameObject* obj);
	gameObject_map* GetEntries(UI32 bitcode);
protected:
	std::unordered_map<UI32, std::unique_ptr<gameObject_map>> mMap;
};

