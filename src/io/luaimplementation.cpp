#include "luaimplementation.h"
#include "../types/gameobject.h"
#include "../types/components/input.h"
#include "../types/components/transform.h"
#include "../types/components/collision.h"
#include "../types/systems/rendersystem.h"
#include "../manager.h"
#include "../eventmanager.h"
#include "resources.h"
#include "../types/vectors.h"

sol::state* LuaImplementation::lua;

void LuaImplementation::Init() {
	if (lua == nullptr) {
		lua = new sol::state();
		lua->open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string);
		CreateBindings();
	}
}

void LuaImplementation::Destroy() {
	delete lua;
	lua = nullptr;
}

void func() {

}

void LuaImplementation::CreateBindings() {
	lua->new_usertype<GameObject>("GameObject",
		"new", sol::no_constructor,
		"create", &GameObject::Create,
		"getID", &GameObject::GetID,
		"transform", sol::readonly(&GameObject::transform),
		"getTransformComponent", &GameObject::GetComponent<Transform>,
		"getInputComponent", &GameObject::GetComponent<Input>,
		"getCollisionComponent", &GameObject::GetComponent<Collision>);

	//// Components
	lua->new_usertype<Component>("Component",
		"new", sol::no_constructor);

	lua->new_usertype<Transform>("Transform",
		sol::base_classes, sol::bases<Component>(),
		"new", sol::no_constructor,
		"setPosition", &Transform::SetLocalPosition,
		"getLocalPosition", &Transform::GetLocalPosition,
		"getWorldPosition", &Transform::GetWorldPosition,
		"setScale", &Transform::SetScale);

	lua->new_usertype<Input>("Input",
		sol::base_classes, sol::bases<Component>(),
		"new", sol::no_constructor,
		"getKeyDown", &Input::GetKeyDown,
		"getKeyUp", &Input::GetKeyUp,
		"isKeyPressed", &Input::IsKeyPressed,
		"getControllerButtonDown", &Input::GetControllerButtonDown,
		"getControllerButtonUp", &Input::GetControllerButtonUp,
		"isControllerButtonPressed", &Input::IsControllerButtonPressed,
		"getControllerLeftAxis", &Input::GetControllerLeftAxis,
		"getControllerRightAxis", &Input::GetControllerRightAxis,
		"getControllerLeftTrigger", &Input::GetControllerLeftTrigger,
		"getControllerRightTrigger", &Input::GetControllerRightTrigger,
		"setController", &Input::SetController);

	lua->new_usertype<Collision>("Collision",
		sol::base_classes, sol::bases<Component>(),
		"new", sol::no_constructor,
		"body", &Collision::body,
		"setLinearVelocity", &Collision::SetLinearVelocity,
		"setAngularVelocity", &Collision::SetAngularVelocity,
		"setCollisionFunc", &Collision::SetCollisionFunc);

	//// Systems
	lua->new_usertype<SystemProgram>("SystemProgram",
		"new", sol::no_constructor);

	lua->new_usertype<RenderSystem>("RenderSystem",
		sol::base_classes, sol::bases<SystemProgram>(),
		"new", sol::no_constructor,
		"setBackgroundColor", &RenderSystem::SetBackgroundColor,
		"setShowFPS", &RenderSystem::SetShowFPS,
		"setShowCollisions", &RenderSystem::SetShowCollisions);

	lua->new_usertype<Manager>("Manager",
		"new", sol::no_constructor,
		"getGameObjectByID", &Manager::GetGameObjectByID,
		"getRenderSystem", &Manager::GetSystem<RenderSystem>,
		"getInstance", &Manager::GetInstance);
	//Error when using other method ^ for extended periods of time, change to this if error in wrapper.hpp : 149 where pointer to function gets garbage address
	//Also, getInstance will crash with top method, with bottom method it will say not existing, using both will work for some reason
	(*lua)["Manager"]["instantiate"] = &Manager::Instantiate;
	(*lua)["Manager"]["destroy"] = &Manager::Destroy;
	(*lua)["Manager"]["getInstance"] = &Manager::GetInstance;

	lua->new_usertype<Manager>("EventManager",
		"new", sol::no_constructor,
		"subscribe", &EventManager::Subscribe,
		"fireEvent", &EventManager::FireEvent);

	lua->new_usertype<b2Vec2>("Vec2",
		sol::constructors<b2Vec2(), b2Vec2(float, float)>(),
		"x", &b2Vec2::x,
		"y", &b2Vec2::y,
		"length", &b2Vec2::Length,
		"set", &b2Vec2::Set,
		"normalize", &b2Vec2::Normalize);
	lua->set_function("Vec2", 
		[](float x, float y) {return b2Vec2(x, y); }
	);
	lua->set_function("getVector", &GetVector);

	//Resources
	lua->set_function("getPrefab", &Resources::GetPrefab);

	//Conversions

	lua->set_function("voidToString", [](void* data) {return (const char*)data; });
	lua->set_function("stringToVoid", [](const char* data) {return (void*)data; });
	lua->set_function("voidToInt", [](void* data) {return ((int)data); });
	lua->set_function("intToVoid", [](I32 data) {return ((void*)data); });
	lua->set_function("voidToBool", [](void* data) {return ((bool)data); });
	lua->set_function("boolToVoid", [](bool data) {return ((void*)data); });
	//lua["Manager"]["getInstance"] = &Manager::GetManager;
}