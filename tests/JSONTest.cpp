#include <gtest/gtest.h>
#include "iNOBEngine.h"

std::string loadClipString =
R"(
{
	"AnimationClips": [{
		"name": "player_idle",
		"texture": "THIS_TEXTURE_SHOULD_NOT_EXIST",
		"looping": false,
		"frames": [{
			"length": 4,
			"coords": [0, 0, 2, 2]
		}]
	}]
}
)";

TEST(JsonTest, LoadClip) {
	nlohmann::json json = nlohmann::json::parse(loadClipString);
	std::vector<AnimationClip> clips;
	json.at("AnimationClips").get_to(clips);
	AnimationCoords compare = AnimationCoords(0, 0, 2, 2);
	ASSERT_EQ(clips.at(0).frames.size(), 1);
	ASSERT_EQ(clips.at(0).frames.at(0).length, 4);
	ASSERT_EQ(clips.at(0).frames.at(0).coords.bottomRight.y, compare.bottomRight.y);
}

std::string prefabMultipleChildren =
R"(
{
	"GameObject": {
		"name": "Ship",
		"components": [{
			"name": "Transform",
			"position": [0.0, 0.0]
		}],
		"children": [{
				"GameObject": {
					"name": "ShipChild",
					"components": [{
						"name": "Transform",
						"position": [1.0, 0.0]
					}],
					"children": [{
						"GameObject": {
							"name": "ShipChildChild",
							"components": [{
								"name": "Transform",
								"position": [2.0, 0.0]
							}]
						}
					}]
				}
			},
			{
				"GameObject": {
					"name": "ShipChild2",
					"components": [{
						"name": "Transform",
						"position": [1.0, 1.0]
					}]
				}
			}
		]
	}
}
)";

TEST(JsonTest, LoadPrefab_MultipleChildren) {
	GameObject* obj = GameObject::LoadFromFile(prefabMultipleChildren);
	ASSERT_EQ(obj->transform->GetLocalPosition(), Vec3f(0, 0, 0));
}

std::string b2Vec2String = 
R"(
[
	[0, 0],
	[1, 0],
	[0, 1]
]
)";

TEST(JsonTest, Loadb2Vec2) {
	nlohmann::json vecJSON = nlohmann::json::parse(b2Vec2String);
	b2Vec2 vec;
	vecJSON.at(2).get_to(vec);
	ASSERT_EQ(vec, b2Vec2(0, 1));
}

TEST(JsonTest, Loadb2Vec2_Array) {
	nlohmann::json vecJSON = nlohmann::json::parse(b2Vec2String);
	std::vector<b2Vec2> vecs;
	vecJSON.get_to(vecs);
	std::vector<b2Vec2> answer = { b2Vec2(0, 0), b2Vec2(1, 0), b2Vec2(0, 1) };
	ASSERT_EQ(vecs, answer);
}

std::string collisionJSON = R"(
{
	"type" : "dynamic",
	"bodydef" : [
	{
		"type" : "polygon",
		"coords" : [
		[-0.40625, -0.375],
		[0.40625, -0.375],
		[0.40625, -0.1875],
		[0, 0.375],
		[-0.40625, -0.1875]
		]
	}
	]
}
)";

TEST(JsonTest, LoadCollsionComponent) {
	nlohmann::json JSON = nlohmann::json::parse(collisionJSON);
	Collision collision;
	JSON.get_to(collision);
	///TODO Add conditions
}

TEST(JsonTest, StringToBin) {
	UI16 a = stringToBin("0010");
	ASSERT_EQ(a, 2);
	UI16 b = stringToBin("0011");
	ASSERT_EQ(b, 3);
}