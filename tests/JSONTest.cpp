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
	ASSERT_EQ(obj->transform->GetLocalPosition(), b2Vec2(0, 0));
}