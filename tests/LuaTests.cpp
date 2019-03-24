#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(LuaTest, CreateGameObject) {
	LuaImplementation::Init();
	LuaImplementation::lua->script("object = GameObject.create()");
	LuaImplementation::lua->script("x = object:getID()");
	UI32 id = LuaImplementation::lua->get<UI32>("x");
	ASSERT_EQ(id, 0);
	LuaImplementation::Destroy();
}

TEST(LuaTest, AddGameObjectToManager) {
	LuaImplementation::Init();
	LuaImplementation::lua->script(R"(
object = GameObject.create()
manager = Manager.getInstance()
manager:instantiate(object, "", Vec2(0,0)))");
	GameObject* obj = Manager::GetInstance()->GetGameObjectByID(1);
	ASSERT_NE(obj, nullptr);
	Manager* manager = Manager::GetInstance();
	LuaImplementation::Destroy();
	delete(manager);
}

/*TEST(LuaTest, AddGameObjectToManager_InitializeVec2) {
	LuaImplementation::Init();
	LuaImplementation::lua->script(R"(
object = GameObject.create()
manager = Manager.getInstance()
manager:instantiate(object, "", Vec2(1,0)))");
	Manager* managers = Manager::GetInstance();
	GameObject* obj = Manager::GetInstance()->GetGameObjectByID(1);
	ASSERT_EQ(obj->GetComponent<Transform>()->position.x, 1);
	Manager* manager = Manager::GetInstance();
	LuaImplementation::Destroy();
	delete(manager);
}*/