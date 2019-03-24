#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(ComponentTest, TransformCreation) {
	Transform *transform = new Transform();
	ASSERT_NE(transform, nullptr);

}

TEST(ComponentTest, GetBitcode) {
	Transform transform;
	ASSERT_EQ(transform.GetBitcode(), Component::TYPE::TRANSFORM);
}

TEST(ComponentTest, GetParent) {
	GameObject *obj = new GameObject();
	Transform transform(obj);
	ASSERT_EQ(obj,transform.GetParent() );
}

TEST(ComponentTest, ToJSON_TestComponent) {
	TestComponent testComponent(100, "test", b2Vec2(3,4));
	nlohmann::json j = testComponent;
	auto component = j.get<TestComponent>();
	ASSERT_EQ(component.position.x, testComponent.position.x);

}

TEST(ComponentTest, ToJSON_Transform) {
	Transform transformComponent(b2Vec2(3, 4));
	nlohmann::json j = transformComponent;
	auto component = j.get<Transform>();
	ASSERT_EQ(component.GetLocalPosition().x, transformComponent.GetLocalPosition().x);

}