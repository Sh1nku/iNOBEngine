#include <filesystem>
#include "resources.h"
#include "types/gameobject.h"
#include "fileutils.h"
namespace fs = std::filesystem;

std::unordered_map<std::string, std::unique_ptr<GameObject>> Resources::prefabs;
std::unordered_map<std::string, std::unique_ptr<Sound>> Resources::sounds;
std::unordered_map<std::string, std::unique_ptr<AnimationClip>> Resources::clips;
std::unordered_map<std::string, std::unique_ptr<Texture>> Resources::textures;

GameObject* Resources::GetPrefab(std::string& name) {
	return prefabs.at(name).get();
}

void Resources::Load(std::string directory) {
	FileUtils::GetFileToString(directory + "/animationClips.clips");
	for (auto& p : fs::recursive_directory_iterator(directory)) {
		if (p.is_regular_file() && p.path().extension() == "prfb") {
			prefabs.insert({ p.path().stem().string(), std::make_unique<GameObject>(GameObject::LoadFromFile(FileUtils::GetFileToString(p.path().string()))) });
		}
	}
}

void loadClips(std::string& contents) {
	nlohmann::json jsonAll = nlohmann::json::parse(contents);
	std::vector<nlohmann::json> clips;
	jsonAll.at("animationClips").get_to(clips);
	for (nlohmann::json& clip : clips) {
		
	}
}

AnimationClip* Resources::GetClip(std::string& clip) {
	return clips.at(clip).get();
}