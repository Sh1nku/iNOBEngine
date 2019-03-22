#include <filesystem>
#include "resources.h"
#include "types/gameobject.h"
#include "fileutils.h"
namespace fs = std::filesystem;

std::unordered_map<std::string, GameObject*> Resources::prefabs;
std::unordered_map<std::string, Sound*> Resources::sounds;
std::unordered_map<std::string, Texture*> Resources::textures;

GameObject* Resources::GetPrefab(std::string name) {
	return prefabs.at(name);
}

void Resources::Load(std::string directory) {
	for (auto& p : fs::recursive_directory_iterator(directory)) {
		if (p.is_regular_file() && p.path().extension() == "prfb") {
			prefabs.emplace(p.path().stem(), GameObject::LoadFromFile(FileUtils::GetFileToString(p.path().string())));
		}
	}
}