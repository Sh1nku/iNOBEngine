#include <iNOBEngine.h>

int main(int argc, char **argv) {
	bool quit = false;
	LuaImplementation::Init();
	Resources::Load("../examples/AsteroidAvoidanceGame/game");
	{
		Animation anim;
		Transform transform;
		Camera camera;
		TestComponent component;
		ScriptComponent scriptComponent;
		Input input;
		UIComponent uiComponent;
	}
	Manager* manager = Manager::GetInstance();
	manager->AddSystem(new AnimationSystem());
	manager->AddSystem(new RenderSystem());
	manager->AddSystem(new ScriptSystem());
	manager->AddSystem(new InputSystem());
	Resources::LoadScene((std::string)"game.scene");
	EventManager::Subscribe("QUIT", [&](void* data) {
		quit = true; 
	});

	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	double deltaTime = 0;

	while (!quit) {
		last = now;
		now = SDL_GetPerformanceCounter();
		deltaTime = (double)((now - last)/ (double)SDL_GetPerformanceFrequency());
		manager->Update(deltaTime);
	}
	return 0;
}