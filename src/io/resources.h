#pragma once
#include <unordered_map>

class GameObject;

class Resources {
public:
	static GameObject* GetPrefab(std::string name);
private:
	static std::unordered_map<std::string, GameObject> prefabs;
};