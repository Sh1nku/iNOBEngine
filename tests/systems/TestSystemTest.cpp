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
	ASSERT_EQ(6, ((TestComponent*)obj->GetComponent("TestComponent"))->value);
	delete obj;
	delete testSystem;
}

TEST(TestSystemTest, TestSystem_ActiveGameObject) {

	TestSystem *testSystem = new TestSystem();
	GameObject *obj = new GameObject();
	TestComponent *component = new TestComponent();
	obj->AddComponent(component);
	testSystem->AddToSystem(obj);
	testSystem->Update(0);
	obj->active = false;
	testSystem->Update(0);
	obj->active = true;
	testSystem->Update(0);
	ASSERT_EQ(4, ((TestComponent*)obj->GetComponent("TestComponent"))->value);
	delete obj;
	delete testSystem;
}