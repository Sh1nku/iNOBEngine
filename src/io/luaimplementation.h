//Handles the implementation of lua through a static sol::state object

#pragma once
#include <sol.hpp>


class LuaImplementation {
public:
	static sol::state *lua;
	static void Init();
	static void Destroy();
	static sol::state* GetState();
private:
	static void CreateBindings();
};