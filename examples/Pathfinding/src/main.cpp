#include <iNOBEngine.h>

int main(int argc, char **argv) {
	bool quit = false;
	LuaImplementation::Init();
	Resources::Load("../examples/Pathfinding/game");
	Manager* manager = Manager::GetInstance();
	manager->AddSystem(new RenderSystem());
	manager->AddSystem(new ScriptSystem());
	manager->AddSystem(new InputSystem());
	Resources::LoadScene((std::string)"pathfinding.scene");
	manager->Subscribe(nullptr,"QUIT",nullptr, [&](void* data) {
		quit = true; 
	});

	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	double deltaTime = 0;
	while (!quit) {
		last = now;
		now = SDL_GetPerformanceCounter();
		deltaTime = (double)((now - last)/ (double)SDL_GetPerformanceFrequency());
		manager->Update(((float)deltaTime));
	}
	return 0;
}