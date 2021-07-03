#include <filesystem>
#include <SDL.h>
#include "resources.h"
#include "../types/script.h"
#include "../types/gameobject.h"
#include "fileutils.h"
#include "texture.h"
#include "scene.h"
#include "../manager.h"
#include "luaimplementation.h"
namespace fs = std::filesystem;

std::unordered_map<std::string, std::unique_ptr<GameObject>> Resources::prefabs;
std::unordered_map<std::string, std::unique_ptr<Sound>> Resources::sounds;
std::unordered_map<std::string, std::unique_ptr<AnimationClip>> Resources::clips;
std::unordered_map<std::string, std::unique_ptr<Texture>> Resources::textures;
std::unordered_map<std::string, std::string> Resources::scenes;
std::unordered_map<std::string, std::unique_ptr<Script>> Resources::scripts;
std::vector<std::pair<std::string, Texture*>> Resources::textureBacklog;
std::vector<std::filesystem::directory_entry> Resources::prefabBacklog;
std::string Resources::gameDir = "";

GameObject* Resources::GetPrefab(const std::string& name) {
	GameObject* obj = new GameObject(*(prefabs.at(name).get()));
	return obj;
}

Texture* Resources::GetTexture(const std::string& name) {
	Texture* tex = nullptr;
	try {
		Texture* tex = textures.at(name).get();
	}
	catch (std::exception) {
		try {
			tex = textures.at("error_texture").get();
		}
		catch (std::exception) {
			Resources::textures.emplace("error_texture", std::move(Texture::LoadTexture("THIS_FILE_SHOULD_NOT_EXIST")));
			tex = textures.at("error_texture").get();
		}
	}
	return tex;
}

Script* Resources::GetScript(const std::string& name) {
	return scripts.at(name).get();
}

void loadClips(const std::string& contents) {
	nlohmann::json jsonAll = nlohmann::json::parse(contents);
	std::vector<nlohmann::json> clips;
	jsonAll.at("AnimationClips").get_to(clips);
	for (nlohmann::json& clip : clips) {
		std::string clipName = clip.at("name");
		std::unique_ptr animationClip = std::make_unique<AnimationClip>();
		clip.get_to(*animationClip.get());
		animationClip.get()->name = clipName;
		Resources::clips.emplace(clipName, std::move(animationClip));
		Resources::clips;
	}
}

void Resources::Load(std::string directory) {
	Resources::gameDir = directory + "/";
	loadClips(FileUtils::GetFileToString(gameDir + "animationClips.clips"));
	for (auto& p : fs::recursive_directory_iterator(directory)) {
		auto ex = p.path().extension();
		if (p.is_regular_file() && p.path().extension() == ".prfb") {
			prefabBacklog.emplace_back(p.path().string());
		}
		else if (p.is_regular_file() && p.path().extension() == ".scene") {
			std::string path = p.path().generic_string();
			path.erase(0, gameDir.length());
			scenes.insert({ path, p.path().string() });
		}
		else if (p.is_regular_file() && p.path().extension() == ".lua") {
			LuaImplementation::Init();
			std::string path = p.path().generic_string();
			path.erase(0, gameDir.length());
			scripts.insert({ path, std::make_unique<Script>(FileUtils::GetFileToString(p.path().string())) });
		}
	}
	for (auto& p : prefabBacklog) {
		GameObject* obj = GameObject::LoadFromFile(FileUtils::GetFileToString(p.path().string()));
		prefabs.insert({ p.path().stem().string(), std::make_unique<GameObject>(*obj) });
	}
	prefabBacklog.clear();

}

///TODO Implement with proper copy constructors for gameobjects and all subobjects
void Resources::LoadScene(const std::string& name) {

	Manager* manager = Manager::GetInstance();
	auto tempGameObjecs = manager->GetGameObjects();
	std::map<UI32, GameObject*> topObjects;
	for (auto& obj : tempGameObjecs) {
		if (obj.second->GetParent() == nullptr) {
			topObjects.emplace(obj);
		}
	}
	for (auto& obj : topObjects) {
		manager->RemoveChildrenIfDontRetain(obj.second);
	}
	
	if (name != "__TEST_FILE__") {
		Scene* scene = Scene::LoadFromFile(FileUtils::GetFileToString(scenes.at(name)));
		for (GameObject* obj : scene->mSceneObjects) {
			manager->Instantiate(obj);
		}
		delete scene;
	}
}

const auto loadErrorClip = [] {
	std::unique_ptr errorClip = std::make_unique<AnimationClip>();
	errorClip.get()->AddFrame(AnimationFrame(AnimationCoords(0, 0, 2, 2), 0));
	errorClip.get()->texture = Resources::GetTexture(std::string("error_texture"));
	Resources::clips.emplace("error_clip", std::move(errorClip));
	return true;
}();

AnimationClip* Resources::GetClip(const std::string& clip) {
	return clips.at(clip).get();
}

std::unordered_map<std::string, std::unique_ptr<AnimationClip>>* Resources::GetClips() {
	return &clips;
}

std::unordered_map<std::string, std::unique_ptr<GameObject>>* Resources::GetPrefabs() {
	return &prefabs;
}