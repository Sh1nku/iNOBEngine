#pragma once
#include <unordered_map>
#include "texture.h"
#include "sound.h"

class GameObject;

class Resources {
public:
	static void Load(std::string directory);
	static GameObject* GetPrefab(std::string& name);
	static AnimationClip* GetClip(std::string& name);
	static Texture* GetTexture(std::string& name);
	static std::unordered_map<std::string, std::unique_ptr<GameObject>> prefabs;
	static std::unordered_map<std::string, std::unique_ptr<Sound>> sounds;
	static std::unordered_map<std::string, std::unique_ptr<AnimationClip>> clips;
	static std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
private:
};