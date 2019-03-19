#include <iostream>
#include "types/gameobject.h"
#include "window/window.h"
#include "io/settings.h"
#include "io/luaimplementation.h"

int main(int argc, char* args[])
{
	Settings::Load();
	LuaImplementation::Init();

	GameObject g;
	Window w;
	w.Create();

	system("pause");
	return 0;

}