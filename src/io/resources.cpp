#include "resources.h"
#include "types\gameobject.h"

std::unordered_map<std::string, GameObject> Resources::prefabs;

GameObject* Resources::GetPrefab(std::string name) {
	return &prefabs.at(name);
}