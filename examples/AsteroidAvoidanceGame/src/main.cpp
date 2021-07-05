#include <iNOBEngine.h>

int main(int argc, char **argv) {
	// Init GUI, HOLY FUCKING SHIT; THIS NEEDS TO BE AS EARLY IN THE APPLICATION AS POSSIBLE, OR ELSE IT WILL SPAWN MULTIPLE WINDOWS USING THE ACTUAL MAIN FUNCTION, WHAT A FUCKING USELESS FEATURE
	//https://www.magpcss.org/ceforum/viewtopic.php?f=6&t=11977
	CefMainArgs args;
	{
		CefExecuteProcess(args, nullptr, nullptr);
	}
	
	bool quit = false;
	LuaImplementation::Init();


	Resources::Load("../examples/AsteroidAvoidanceGame/game");
	Manager* manager = Manager::GetInstance();
	manager->AddSystem(new AnimationSystem());
	manager->AddSystem(new RenderSystem());
	manager->AddSystem(new ScriptSystem());
	manager->AddSystem(new InputSystem());
	manager->AddSystem(new CollisionSystem());
	Resources::LoadScene((std::string)"menu.scene");
	manager->Subscribe(nullptr,"QUIT",nullptr, [&](void* data) {
		quit = true; 
	});

	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	double deltaTime = 0;
    while (!quit) {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
        manager->Update(((float)deltaTime));
    }
	return 0;
}