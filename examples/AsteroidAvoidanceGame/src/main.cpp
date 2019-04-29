#include <iNOBEngine.h>

int main(int argc, char **argv) {
	Resources::Load("../examples/AsteroidAvoidanceGame/game");
	Resources::scenes;
	{
		Animation anim;
		Transform transform;
		Camera camera;
		TestComponent component;
	}
	Manager* manager = Manager::GetInstance();
	manager->AddSystem(new RenderSystem());
	Resources::LoadScene((std::string)"game");
	while (true) {
		manager->Update(0);
	}
	return 0;
}