#pragma once
#include <vector>
#include "../types/gameobject.h"

class Resources;

class Scene {
public:
	friend class Resources;
	Scene();
	~Scene();
	static Scene* LoadFromFile(std::string& fileContents);
private:
	std::vector<GameObject*> mSceneObjects;
};