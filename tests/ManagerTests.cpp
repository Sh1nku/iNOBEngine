#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(ManagerTest, GetSystem) {
	Manager *manager = Manager::GetInstance();
	TestSystem* testSystem = new TestSystem();
	manager->AddSystem(testSystem);
	TestSystem* testSystem2 = manager->GetSystem<TestSystem>();
	ASSERT_EQ(testSystem, testSystem2);
	delete(manager);
}

TEST(ManagerTest, GetSystem_Non_Existent) {
	Manager *manager = Manager::GetInstance();
	TestSystem* testSystem = manager->GetSystem<TestSystem>();
	ASSERT_EQ(nullptr, testSystem);
	delete(manager);
}

TEST(ManagerTest, GetSystem_From_Multiple) {
	Manager* manager = Manager::GetInstance();
	TestSystem* testSystem = new TestSystem();
	manager->AddSystem((SystemProgram*)testSystem);
	RenderSystem* renderSystem = new RenderSystem();
	manager->AddSystem((SystemProgram*)renderSystem);
	RenderSystem* renderSystem2 = manager->GetSystem<RenderSystem>();
	ASSERT_EQ(renderSystem, renderSystem2);
	delete manager;
}

TEST(ManagerTest, AddSystem) {
	Manager *manager = Manager::GetInstance();
	TestSystem* testSystem = (TestSystem*)manager->AddSystem(new TestSystem());
	ASSERT_NE(nullptr, testSystem);
	delete(manager);
}

TEST(ManagerTest, AddGameObject) {
	Manager* manager = Manager::GetInstance();
	GameObject* gameObject = new GameObject();
	manager->Instantiate(gameObject);
	GameObject* gameObject2 = manager->GetGameObjectByID(gameObject->GetID());
	ASSERT_EQ(gameObject, gameObject2);
	manager->Destroy(gameObject);
	delete(manager);
}

TEST(ManagerTest, GetGameObjectByID) {
	Manager* manager = Manager::GetInstance();
	GameObject* gameObject = new GameObject();
	manager->Instantiate(gameObject);
	GameObject* gameObject2 = new GameObject();
	manager->Instantiate(gameObject2);
	GameObject* gameObject3 = manager->GetGameObjectByID(gameObject->GetID());
	ASSERT_EQ(gameObject, gameObject3);
	manager->Destroy(gameObject);
	manager->Destroy(gameObject2);
	delete(manager);
}

TEST(ManagerTest, GetGameObjectByID_Non_Existent) {
	Manager* manager = Manager::GetInstance();
	GameObject* gameObject = manager->GetGameObjectByID(1000);
	ASSERT_EQ(nullptr, gameObject);
	delete(manager);
}

TEST(ManagerTest, GetGameObjectByName) {
	Manager* manager = Manager::GetInstance();
	GameObject* gameObject = new GameObject();
	manager->Instantiate(gameObject, "test");
	GameObject* gameObject2 = new GameObject();
	manager->Instantiate(gameObject2, "test2");
	GameObject* gameObject3 = manager->GetGameObjectByName("test2");
	ASSERT_EQ(gameObject2, gameObject3);
	manager->Destroy(gameObject);
	manager->Destroy(gameObject2);
	delete(manager);
}

TEST(ManagerTest, GetGameObjectByName_Non_Existent) {
	Manager* manager = Manager::GetInstance();
	GameObject* gameObject = manager->GetGameObjectByName("test");
	ASSERT_EQ(nullptr, gameObject);
	delete(manager);
}

TEST(ManagerTest, Destroy_Chain_GameObjects) {
	Manager* manager = Manager::GetInstance();
	GameObject* obj = new GameObject();
	GameObject* obj2 = new GameObject(obj);
	GameObject* obj3 = new GameObject(obj2);
	manager->Instantiate(obj);
	manager->Destroy(obj);
	delete(manager);
}