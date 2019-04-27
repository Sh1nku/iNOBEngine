#include "luaimplementation.h"
#include "../types/gameobject.h"
#include "../manager.h"

sol::state* LuaImplementation::lua;

void LuaImplementation::Init() {
	lua = new sol::state();
	lua->open_libraries(sol::lib::base, sol::lib::package);
	CreateBindings();
}

void LuaImplementation::Destroy() {
	delete lua;
}

void LuaImplementation::CreateBindings() {
	lua->new_usertype<GameObject>("GameObject",
		"new", sol::no_constructor,
		"create", &GameObject::Create,
		"getID", &GameObject::GetID);
	lua->new_usertype<Manager>("Manager",
		"new", sol::no_constructor,
		"getInstance", &Manager::GetInstance,
		"instantiate", &Manager::Instantiate);
	lua->set_function("Vec2", 
		[](float x, float y) {return b2Vec2(x, y); }
	);
	//lua["Manager"]["getInstance"] = &Manager::GetManager;
}