#include "luaimplementation.h"
#include "../types/gameobject.h"
#include "../types/components/input.h"
#include "../types/components/transform.h"
#include "../types/components/collision.h"
#include "../types/components/animation.h"
#include "../types/systems/rendersystem.h"
#include "../types/systems/collisionsystem.h"
#include "../types/systems/animationsystem.h"
#include "../types/systems/scriptsystem.h"
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
		"active", &GameObject::active,
		"transform", sol::readonly(&GameObject::transform),
		"getTransformComponent", &GameObject::GetComponent<Transform>,
		"getInputComponent", &GameObject::GetComponent<Input>,
		"getCollisionComponent", &GameObject::GetComponent<Collision>,
		"getAnimationComponent", &GameObject::GetComponent<Animation>);

	//// Components
	lua->new_usertype<Component>("Component",
		"new", sol::no_constructor,
		"getParent", &Component::GetParent);

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
		"setLinearVelocity", [](Collision& obj, Vec2f& vel) {obj.SetLinearVelocity(Vec2fToB2Vec2(vel)); },
		"setAngularVelocity", &Collision::SetAngularVelocity,
		"setCollisionFunc", &Collision::SetCollisionFunc);

	lua->new_usertype<Animation>("Animation",
		sol::base_classes, sol::bases<Component>(),
		"new", sol::no_constructor,
		"setClip", &Animation::SetClip);

	//// Systems
	lua->new_usertype<SystemProgram>("SystemProgram",
		"new", sol::no_constructor,
		"active", &SystemProgram::active);

	lua->new_usertype<RenderSystem>("RenderSystem",
		sol::base_classes, sol::bases<SystemProgram>(),
		"new", sol::no_constructor,
		"setBackgroundColor", &RenderSystem::SetBackgroundColor,
		"setShowFPS", &RenderSystem::SetShowFPS,
		"setShowCollisions", &RenderSystem::SetShowCollisions);

	lua->new_usertype<AnimationSystem>("AnimationSystem",
		sol::base_classes, sol::bases<SystemProgram>(),
		"new", sol::no_constructor);

	lua->new_usertype<ScriptSystem>("ScriptSystem",
		sol::base_classes, sol::bases<SystemProgram>(),
		"new", sol::no_constructor);

	lua->new_usertype<CollisionSystem>("CollisionSystem",
		sol::base_classes, sol::bases<SystemProgram>(),
		"new", sol::no_constructor);

	lua->new_usertype<Manager>("Manager",
		"new", sol::no_constructor,
		"getGameObjectByID", &Manager::GetGameObjectByID,
		"getGameObjectByName", &Manager::GetGameObjectByName,
		"getRenderSystem", &Manager::GetSystem<RenderSystem>,
		"getAnimationSystem", &Manager::GetSystem<AnimationSystem>,
		"getCollisionSystem", &Manager::GetSystem<CollisionSystem>,
		"getScriptSystem", &Manager::GetSystem<ScriptSystem>,
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

	lua->new_usertype<Vec2f>("Vec2",
		sol::constructors<Vec2f(), Vec2f(float, float)>(),
		"x", &Vec2f::x,
		"y", &Vec2f::y,
		"length", &Vec2f::length,
		//Example capture object
		//"set", [](b2Vec2& obj, float newX, float newY) {obj.x = newX; obj.y = newY; },
		"set", [](Vec2f &obj, float x, float y) {obj.x = x; obj.y = y; },
		"normalize", [](Vec2f &obj) {obj = glm::normalize(obj); });
	lua->set_function("Vec2", 
		[](float x, float y) {return Vec2f(x, y); }
	);

	lua->new_usertype<Vec3f>("Vec3",
		sol::constructors<Vec3f(), Vec3f(float, float, float)>(),
		"x", &Vec3f::x,
		"y", &Vec3f::y,
		"z", &Vec3f::z,
		"length", &Vec3f::length,
		//Example capture object
		//"set", [](b2Vec2& obj, float newX, float newY) {obj.x = newX; obj.y = newY; },
		"set", [](Vec3f &obj, float x, float y, float z) {obj.x = x; obj.y = y; obj.z = z; },
		"normalize", [](Vec3f &obj) {obj = glm::normalize(obj);});
	lua->set_function("Vec3",
		[](float x, float y, float z) {return Vec3f(x, y, z); }
	);

	lua->set_function("getVector2f", &GetVector2f);
	lua->set_function("getVector3f", &GetVector3f);

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

sol::state* LuaImplementation::GetState() {
	return lua;
}