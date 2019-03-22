#pragma once
#include <unordered_map>
#include "texture.h"
#include "sound.h"

class GameObject;

class Resources {
public:
	static void Load(std::string directory);
	static GameObject* GetPrefab(std::string name);
private:
	static std::unordered_map<std::string, GameObject*> prefabs;
	static std::unordered_map<std::string, Sound*> sounds;
	static std::unordered_map<std::string, Texture*> textures;
};