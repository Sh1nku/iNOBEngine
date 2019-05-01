#include "script.h"
#include "../io/luaimplementation.h"
#include "gameobject.h"

Script::Script(std::string text) : text(text) {

	env = new sol::environment(*LuaImplementation::lua, sol::create, LuaImplementation::lua->globals());
	started = false;
	LuaImplementation::lua->script(text, *env);
}

Script::~Script() {
	delete env;
}

Script::Script(const Script& old) {
	env = new sol::environment(*LuaImplementation::lua, sol::create, LuaImplementation::lua->globals());
	text = old.text.c_str();
	started = false;
	LuaImplementation::lua->script(text, *env);
}

void Script::SetGameObject(GameObject* obj) {
	(*env)["localObject"] = obj;
}

void Script::Start() {
	(*env)["start"]();
}

void Script::Update(float dt) {
	(*env)["update"](dt);
}