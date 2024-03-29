#include <gtest/gtest.h>
#include "iNOBEngine.h"
#include <fstream>

unsigned char pngImage[] {
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
	0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x08, 0x06, 0x00, 0x00, 0x00, 0x8D, 0x32, 0xCF,
	0xBD, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x2E, 0x23, 0x00, 0x00, 0x2E,
	0x23, 0x01, 0x78, 0xA5, 0x3F, 0x76, 0x00, 0x00, 0x00, 0x45, 0x49, 0x44, 0x41, 0x54, 0x18, 0x19,
	0x63, 0x6C, 0x9B, 0x96, 0xF7, 0x9F, 0x81, 0x08, 0xC0, 0x44, 0x84, 0x1A, 0xB0, 0x12, 0xEA, 0x2B,
	0x64, 0x7C, 0x2B, 0xA3, 0xF2, 0x7F, 0x66, 0x95, 0x17, 0x56, 0x17, 0xEC, 0xDC, 0x14, 0x07, 0x17,
	0x27, 0x68, 0xB5, 0xBB, 0xDF, 0x22, 0xE2, 0xDC, 0x08, 0x32, 0x15, 0xA4, 0x18, 0x6C, 0x62, 0x7A,
	0xDB, 0x36, 0x06, 0x10, 0xC6, 0x06, 0x40, 0x8A, 0x40, 0x8A, 0x19, 0xA9, 0x1E, 0x8E, 0x00, 0x88,
	0xE7, 0x14, 0xF3, 0xF3, 0x54, 0xC4, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE,
	0x42, 0x60, 0x82, };

std::string clipJson =
R"(
{
	"name": "player_idle",
	"texture": "TEMP_FILE_PNG.png",
	"looping": false,
	"frames": [{
		"length": 0,
		"coords": [0, 0, 10, 10]
	}]
}
)";

std::string testGameObjectJson =
R"(
{
	"GameObject": {
		"name" : "Ship",
		"components" : [{
			"name": "Transform",
			"position" : [1.0, 0.0]
		}]
	}
}
)";

TEST(ResourceTest, LoadPNG_DEPENDS_UI) {
	std::ofstream file;
	file.open("TEMP_FILE_PNG.png", std::ios::binary | std::ios::out);
	file.write((char*)pngImage, sizeof(pngImage));
	file.close();
	Texture* tex = Texture::LoadTexture("TEMP_FILE_PNG.png");
	ASSERT_EQ(tex->GetWidth(), 10);
	ASSERT_EQ(tex->GetComp(), 4);
	delete tex;
	remove("TEMP_FILE_PNG.png");
}

TEST(ResourceTest, InstantiateDestroyAndReinstantiatePrefab) {
	Manager* manager = Manager::GetInstance();
	GameObject *tempObj = GameObject::LoadFromFile(testGameObjectJson);
	Resources::GetPrefabs()->emplace("test_prefab", std::make_unique<GameObject>(*tempObj));
	GameObject* obj = Resources::GetPrefab((std::string)"test_prefab");
	manager->Instantiate(obj);
	manager->Destroy(obj);
	manager->Update(0);
	GameObject* obj2 = Resources::GetPrefab((std::string)"test_prefab");
	manager->Instantiate(obj2);
	ASSERT_EQ(obj2->GetName(), "Ship");
	manager->Destroy(obj2);
	delete manager;
}

TEST(ResourceTest, InstantiatePrefabTwice) {
	Manager* manager = Manager::GetInstance();
	GameObject *tempObj = GameObject::LoadFromFile(testGameObjectJson);
	Resources::GetPrefabs()->emplace("test_prefab", std::make_unique<GameObject>(*tempObj));
	GameObject* obj = Resources::GetPrefab((std::string)"test_prefab");
	GameObject* obj2 = Resources::GetPrefab((std::string)"test_prefab");
	manager->Instantiate(obj);
	manager->Instantiate(obj2);
	manager->Destroy(obj);
	manager->Destroy(obj2);
	delete manager;
}

TEST(RenderSystemTest, ShowTexture_DEPENDS_UI) {
	RenderSystem renderSystem;
	GameObject obj;
	Animation* anim = new Animation();

	std::ofstream file;
	file.open("TEMP_FILE_PNG.png", std::ios::binary | std::ios::out);
	file.write((char*)pngImage, sizeof(pngImage));
	file.close();
	std::unique_ptr<AnimationClip> clip = std::make_unique<AnimationClip>();
	from_json(nlohmann::json::parse(clipJson), *clip.get());
	Resources::GetClips()->insert({ "TestClip", std::move(clip) });
	anim->SetClip(std::string("TestClip"));
	obj.AddComponent(anim);
	obj.AddComponent(new Transform());
	renderSystem.AddToSystem(&obj);
	renderSystem.Update(0);
	SDL_Delay(1000);
	remove("TEMP_FILE_PNG.png");
}