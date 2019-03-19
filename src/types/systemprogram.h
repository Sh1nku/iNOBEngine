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
	std::vector<std::vector<Component*>*>* GetEntries(UI32 bitcode);
protected:
	std::unordered_map<UI32, std::vector<std::vector<Component*>*>*> mMap;
};

