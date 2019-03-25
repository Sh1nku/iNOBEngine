#include <iNOBEngine.h>
#include <gtest/gtest.h>

TEST(TestSystemTest, TestSystem_TestComponent) {

	TestSystem *testSystem = new TestSystem();
	GameObject *obj = new GameObject();
	TestComponent *component = new TestComponent();
	obj->AddComponent(component);
	testSystem->AddToSystem(obj);
	testSystem->Update(0);
	testSystem->Update(0);
	testSystem->Update(0);
	ASSERT_EQ(6, ((TestComponent*)obj->GetComponent(Component::TEST_COMPONENT))->value);
	delete obj;
	delete testSystem;
}