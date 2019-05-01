#include <iNOBEngine.h>

int main(int argc, char **argv) {
	LuaImplementation::Init();
	Resources::Load("../examples/AsteroidAvoidanceGame/game");
	{
		Animation anim;
		Transform transform;
		Camera camera;
		TestComponent component;
		ScriptComponent scriptComponent;
		Input input;
	}
	Manager* manager = Manager::GetInstance();
	manager->AddSystem(new RenderSystem());
	manager->AddSystem(new ScriptSystem());
	manager->AddSystem(new InputSystem());
	Resources::LoadScene((std::string)"game.scene");
	while (true) {
		manager->Update(0);
		SDL_Delay(33);
	}
	return 0;
}