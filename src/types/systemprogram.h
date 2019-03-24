#pragma once

#include <vector>
#include <unordered_map>
#include "enginetypes.h"

class GameObject;
class Component;

class SystemProgram
{
public:
	SystemProgram();
	virtual ~SystemProgram();
	bool active = true;
	virtual void Update(float dt);
	void AddToSystem(GameObject* obj);
	std::unordered_map<GameObject* ,std::unordered_map<UI32,Component*>*>* GetEntries(UI32 bitcode);
protected:
	std::unordered_map<UI32, std::unordered_map<GameObject* ,std::unordered_map<UI32,Component*>*>*> mMap;
};

