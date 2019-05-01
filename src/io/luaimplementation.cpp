#include "luaimplementation.h"
#include "../types/gameobject.h"
#include "../types/components/input.h"
#include "../types/components/transform.h"
#include "../types/systems/rendersystem.h"
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
		"transform", sol::readonly(&GameObject::transform),
		"getTransformComponent", &GameObject::GetComponent<Transform>,
		"getInputComponent", &GameObject::GetComponent<Input>);

	//// Components
	lua->new_usertype<Component>("Component",
		"new", sol::no_constructor);

	lua->new_usertype<Transform>("Transform",
		sol::base_classes, sol::bases<Component>(),
		"new", sol::no_constructor,
		"setPosition", &Transform::SetLocalPosition,
		"getLocalPosition", &Transform::GetLocalPosition,
		"getWorldPosition", &Transform::GetWorldPosition);

	lua->new_usertype<Input>("Input",
		sol::base_classes, sol::bases<Component>(),
		"new", sol::no_constructor,
		"getKeyDown", &Input::GetKeyDown,
		"getKeyUp", &Input::GetKeyUp,
		"isKeyPressed", &Input::IsKeyPressed);

	//// Systems
	lua->new_usertype<SystemProgram>("SystemProgram",
		"new", sol::no_constructor);

	lua->new_usertype<RenderSystem>("RenderSystem",
		sol::base_classes, sol::bases<SystemProgram>(),
		"new", sol::no_constructor,
		"setBackgroundColor", &RenderSystem::SetBackgroundColor);

	lua->new_usertype<Manager>("Manager",
		"new", sol::no_constructor,
		"getInstance", &Manager::GetInstance,
		"instantiate", &Manager::Instantiate,
		"getGameObjectByID", &Manager::GetGameObjectByID,
		"getRenderSystem", &Manager::GetSystem<RenderSystem>);

	lua->new_usertype<b2Vec2>("Vec2",
		sol::constructors<b2Vec2(), b2Vec2(float, float)>(),
		"x", &b2Vec2::x,
		"y", &b2Vec2::y);
	lua->set_function("Vec2", 
		[](float x, float y) {return b2Vec2(x, y); }
	);
	//lua["Manager"]["getInstance"] = &Manager::GetManager;
}