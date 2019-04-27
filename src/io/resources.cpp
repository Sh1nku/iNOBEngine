#include <filesystem>
#include <SDL.h>
#include "resources.h"
#include "types/gameobject.h"
#include "fileutils.h"
#include "texture.h"
namespace fs = std::filesystem;

std::unordered_map<std::string, std::unique_ptr<GameObject>> Resources::prefabs;
std::unordered_map<std::string, std::unique_ptr<Sound>> Resources::sounds;
std::unordered_map<std::string, std::unique_ptr<AnimationClip>> Resources::clips;
std::unordered_map<std::string, std::unique_ptr<Texture>> Resources::textures;
std::vector<std::pair<std::string, Texture*>> Resources::textureBacklog;

GameObject* Resources::GetPrefab(std::string& name) {
	return prefabs.at(name).get();
}

Texture* Resources::GetTexture(std::string& name) {
	Texture* tex = nullptr;
	try {
		Texture* tex = textures.at(name).get();
	}
	catch (std::exception ex) {
		try {
			tex = textures.at("error_texture").get();
		}
		catch (std::exception exs) {
			Resources::textures.emplace("error_texture", std::move(Texture::LoadTexture(std::string("THIS_FILE_SHOULD_NOT_EXIST"))));
			tex = textures.at("error_texture").get();
		}
	}
	return tex;
}

void Resources::Load(std::string directory) {
	FileUtils::GetFileToString(directory + "/animationClips.clips");
	for (auto& p : fs::recursive_directory_iterator(directory)) {
		if (p.is_regular_file() && p.path().extension() == "prfb") {
			prefabs.insert({ p.path().stem().string(), std::make_unique<GameObject>(GameObject::LoadFromFile(FileUtils::GetFileToString(p.path().string()))) });
		}
	}
}

const auto loadErrorClip = [&] {
	std::unique_ptr errorClip = std::make_unique<AnimationClip>();
	errorClip.get()->AddFrame(AnimationFrame(AnimationCoords(0, 0, 1, 1), 0));
	errorClip.get()->texture = Resources::GetTexture(std::string("error_texture"));
	Resources::clips.emplace("error_clip", std::move(errorClip));
	return true;
}();

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