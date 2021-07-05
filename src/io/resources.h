#pragma once
#include <unordered_map>
#include <vector>
#include <utility>
#include <filesystem>
#include "texture.h"
#include "sound.h"

class GameObject;
class Scene;
class Script;

class Resources {
public:
	static void Load(std::string directory);
	static GameObject* GetPrefab(const std::string& name);
	static AnimationClip* GetClip(const std::string& name);
	static Texture* GetTexture(const std::string& name);
	static Script* GetScript(const std::string& name);
	static void LoadScene(const std::string& name);

	static std::unordered_map<std::string, std::unique_ptr<AnimationClip>>* GetClips();
	static std::unordered_map<std::string, std::unique_ptr<GameObject>>* GetPrefabs();

	static std::unordered_map<std::string, std::unique_ptr<GameObject>> prefabs;
	static std::unordered_map<std::string, std::unique_ptr<Sound>> sounds;
	static std::unordered_map<std::string, std::unique_ptr<AnimationClip>> clips;
	static std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
	static std::unordered_map<std::string, std::string> scenes;
	static std::unordered_map<std::string, std::unique_ptr<Script>> scripts;
	static std::vector<std::pair<std::string, Texture*>> textureBacklog;
	static std::vector<std::filesystem::directory_entry> prefabBacklog;
	static std::string gameDir;
	static std::string gameDirAbsoulute;
private:
};