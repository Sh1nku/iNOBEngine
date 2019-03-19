//Handles the implementation of lua through a static sol::state object

#pragma once
#include <sol.hpp>


class LuaImplementation {
public:
	static sol::state *lua;
	static void Init();
	static void Destroy();
private:
	static void CreateBindings();
};