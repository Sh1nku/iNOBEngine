#include "scene.h"
#include <nlohmann/json.hpp>
#include "resources.h"
#include "../types/gameobject.h"

Scene::Scene() {

}

Scene::~Scene() {

}

Scene* Scene::LoadFromFile(std::string& fileContents) {
	Scene* scene = new Scene();
	nlohmann::json json = nlohmann::json::parse(fileContents);
	for (auto gameObjectJSON : json) {
		GameObject* obj = GameObject::LoadFromFile(gameObjectJSON.dump());
		scene->mSceneObjects.emplace_back(obj);
	}
	return scene;
}