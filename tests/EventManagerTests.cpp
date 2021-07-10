#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(EventManagerTests, EventDeletedOnSenderDeletion) {
	Manager* manager = Manager::GetInstance();
	GameObject* obj = new GameObject();
	GameObject* obj2 = new GameObject();
	manager->Instantiate(obj);
	manager->Instantiate(obj2);
	int i = 0;
	obj->Subscribe(obj2, "EVENT", [&](void* data) {
		i = 10;
	});
	manager->Destroy(obj2);
	manager->Update(0);
	obj2->FireEvent("EVENT", nullptr);
	manager->Destroy(obj);
	manager->Update(0);
	ASSERT_EQ(0, i);
	delete(manager);
}

TEST(EventManagerTests, EventDeletedOnRecieverDeletion) {
	Manager* manager = Manager::GetInstance();
	GameObject* obj = new GameObject();
	GameObject* obj2 = new GameObject();
	manager->Instantiate(obj);
	manager->Instantiate(obj2);
	int i = 0;
	obj->Subscribe(obj2, "EVENT", [&](void* data) {
		i = 10;
	});
	manager->Destroy(obj);
	manager->Update(0);
	obj2->FireEvent("EVENT", nullptr);
	manager->Destroy(obj2);
	manager->Update(0);
	ASSERT_EQ(0, i);
	delete(manager);
}
