#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(TransformComponentTest, SetLocalPositionOnParent) {
	GameObject *obj = new GameObject();
	GameObject *obj2 = new GameObject(obj);
	obj->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(10, 0)));
	obj->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(5, 0)));
	ASSERT_EQ(obj->transform->GetWorldPosition().x, obj2->transform->GetWorldPosition().x);
	delete obj;
}

TEST(TransformComponentTest, SetLocalPositionOnParent3Objects) {
	GameObject *obj = new GameObject();
	GameObject *obj2 = new GameObject(obj);
	GameObject *obj3 = new GameObject(obj2);
	obj->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(10, 0)));
	obj->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(5, 0)));
	ASSERT_EQ(obj->transform->GetWorldPosition().x, obj3->transform->GetWorldPosition().x);
	delete obj;
}

TEST(TransformComponentTest, SetLocalPositionOnParentWhenChildHasPosition) {
	GameObject *obj = new GameObject();
	obj->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(2, 0)));
	GameObject *obj2 = new GameObject(obj);
	obj2->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(-2, 0)));
	obj->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(10, 0)));
	ASSERT_EQ(obj2->transform->GetWorldPosition().x, 8);
	obj->transform->SetLocalPosition(&b2Vec2ToVec3f(b2Vec2(5, 0)));
	ASSERT_EQ(obj2->transform->GetWorldPosition().x, 3);
	delete obj;
}