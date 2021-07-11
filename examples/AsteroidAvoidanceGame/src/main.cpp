#include <iNOBEngine.h>


int main(int argc, char **argv) {
	CEF_INIT(argc, argv);
	
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

	CEF_CLOSE();
	return 0;
}