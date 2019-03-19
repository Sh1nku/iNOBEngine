#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(GameObjectTest, Construct) {
	GameObject *gameObject = new GameObject();
	ASSERT_NE(nullptr, gameObject);
	delete gameObject;
}

TEST(GameObjectTest, GetParent) {
	GameObject *gameObject = new GameObject();
	GameObject *gameObject2 = new GameObject(gameObject);
	ASSERT_EQ(gameObject, gameObject2->GetParent());
	delete gameObject;
}

TEST(GameObjectTest, ChainObjects) {
	GameObject *gameObject = new GameObject();
	GameObject *gameObject2 = new GameObject(gameObject);
	GameObject *gameObject3 = new GameObject(gameObject2);
	ASSERT_EQ(gameObject, gameObject3->GetParent()->GetParent());
	delete gameObject;
}

///TODO Assert
TEST(GameObjectTest, ChainObjectsDelete) {
	GameObject *gameObject = new GameObject();
	GameObject *gameObject2 = new GameObject(gameObject);
	GameObject *gameObject3 = new GameObject(gameObject2);
	delete gameObject;
}