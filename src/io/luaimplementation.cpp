#include "luaimplementation.h"
#include "../types/gameobject.h"
#include "../types/components/input.h"
#include "../manager.h"

sol::state* LuaImplementation::lua;

void LuaImplementation::Init() {
	if (lua == nullptr) {
		lua = new sol::state();
		lua->open_libraries(sol::lib::base, sol::lib::package);
		CreateBindings();
	}
}

void LuaImplementation::Destroy() {
	delete lua;
}

void LuaImplementation::CreateBindings() {
	lua->new_usertype<GameObject>("GameObject",
		"new", sol::no_constructor,
		"create", &GameObject::Create,
		"getID", &GameObject::GetID,
		"getTransformComponent", &GameObject::GetComponent<Transform>,
		"getInputComponent", &GameObject::GetComponent<Input>);
	lua->new_usertype<Component>("Component"),
		"new", sol::no_constructor;
	lua->new_usertype<Input>("Input",
		sol::base_classes, sol::bases<Component>(),
		"new", sol::no_constructor,
		"getKeyDown", &Input::GetKeyDown,
		"getKeyUp", &Input::GetKeyUp,
		"isKeyPressed", &Input::IsKeyPressed);
	lua->new_usertype<Manager>("Manager",
		"new", sol::no_constructor,
		"getInstance", &Manager::GetInstance,
		"instantiate", &Manager::Instantiate,
		"getGameObjectByID", &Manager::GetGameObjectByID);
	lua->set_function("Vec2", 
		[](float x, float y) {return b2Vec2(x, y); }
	);
	//lua["Manager"]["getInstance"] = &Manager::GetManager;
}