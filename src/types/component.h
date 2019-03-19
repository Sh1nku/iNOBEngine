#pragma once
#include "enginetypes.h"
#include <json.hpp>
#include <unordered_map>

class GameObject;

class Component
{
public:
	enum TYPE{ COMPONENT = 1 << 0,TRANSFORM = 1 << 1, TEST_COMPONENT = 1 << 2};
	Component(GameObject *parent = nullptr);
	virtual ~Component();

	GameObject *GetParent();

	virtual TYPE GetBitcode() = 0;

protected:
	GameObject *mParent;
};

