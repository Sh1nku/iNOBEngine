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
	manager->AddSystem(new RenderSystem());
	manager->AddSystem(new ScriptSystem());
	manager->AddSystem(new InputSystem());
	Resources::LoadScene((std::string)"game.scene");
	EventManager::Subscribe("QUIT", [&](void* data) {
		quit = true; 
	});
	while (!quit) {
		manager->Update(0);
	}
	return 0;
}