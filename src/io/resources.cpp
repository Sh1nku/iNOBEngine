#include <filesystem>
#include <SDL.h>
#include "resources.h"
#include "../types/gameobject.h"
#include "fileutils.h"
#include "texture.h"
#include "scene.h"
#include "../manager.h"
namespace fs = std::filesystem;

std::unordered_map<std::string, std::unique_ptr<GameObject>> Resources::prefabs;
std::unordered_map<std::string, std::unique_ptr<Sound>> Resources::sounds;
std::unordered_map<std::string, std::unique_ptr<AnimationClip>> Resources::clips;
std::unordered_map<std::string, std::unique_ptr<Texture>> Resources::textures;
std::unordered_map<std::string, std::string> Resources::scenes;
std::vector<std::pair<std::string, Texture*>> Resources::textureBacklog;
std::string Resources::gameDir = "";

GameObject* Resources::GetPrefab(std::string& name) {
	GameObject* obj = new GameObject(*(prefabs.at(name).get()));
	return obj;
}

Texture* Resources::GetTexture(std::string& name) {
	Texture* tex = nullptr;
	try {
		Texture* tex = textures.at(name).get();
	}
	catch (std::exception) {
		try {
			tex = textures.at("error_texture").get();
		}
		catch (std::exception) {
			Resources::textures.emplace("error_texture", std::move(Texture::LoadTexture(std::string("THIS_FILE_SHOULD_NOT_EXIST"))));
			tex = textures.at("error_texture").get();
		}
	}
	return tex;
}

void loadClips(std::string& contents) {
	nlohmann::json jsonAll = nlohmann::json::parse(contents);
	std::vector<nlohmann::json> clips;
	jsonAll.at("AnimationClips").get_to(clips);
	for (nlohmann::json& clip : clips) {
		std::string clipName = clip.at("name");
		std::unique_ptr animationClip = std::make_unique<AnimationClip>();
		clip.get_to(*animationClip.get());
		Resources::clips.emplace(clipName, std::move(animationClip));
	}
}

void Resources::Load(std::string directory) {
	Resources::gameDir = directory + "/";
	loadClips(FileUtils::GetFileToString(gameDir + "animationClips.clips"));
	for (auto& p : fs::recursive_directory_iterator(directory)) {
		auto ex = p.path().extension();
		if (p.is_regular_file() && p.path().extension() == ".prfb") {
			GameObject* obj = GameObject::LoadFromFile(FileUtils::GetFileToString(p.path().string()));
			prefabs.insert({ p.path().stem().string(), std::make_unique<GameObject>(*obj) });
		}
		else if (p.is_regular_file() && p.path().extension() == ".scene") {
			scenes.insert({ p.path().stem().string(), p.path().string() });
		}
	}
}

///TODO Implement with proper copy constructors for gameobjects and all subobjects
void Resources::LoadScene(std::string& name) {
	Scene* scene = Scene::LoadFromFile(FileUtils::GetFileToString(scenes.at((std::string)name)));
	Manager* manager = Manager::GetInstance();
	for (GameObject* obj : scene->mSceneObjects) {
		manager->Instantiate(obj);
	}
	delete scene;
}

const auto loadErrorClip = [&] {
	std::unique_ptr errorClip = std::make_unique<AnimationClip>();
	errorClip.get()->AddFrame(AnimationFrame(AnimationCoords(0, 0, 2, 2), 0));
	errorClip.get()->texture = Resources::GetTexture(std::string("error_texture"));
	Resources::clips.emplace("error_clip", std::move(errorClip));
	return true;
}();

AnimationClip* Resources::GetClip(std::string& clip) {
	return clips.at(clip).get();
}