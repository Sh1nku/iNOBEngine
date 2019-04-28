#include <iNOBEngine.h>

int main(int argc, char **argv) {
	Resources::Load("../examples/AsteroidAvoidanceGame/game");
	{
		Animation anim;
		Transform transform;
		Camera camera;
		TestComponent component;
	}
	Manager* manager = Manager::GetInstance();
	manager->AddSystem(new RenderSystem());
	manager->Instantiate(Resources::GetPrefab(std::string("ship")));
	while (true) {
		manager->Update(0);
	}
	return 0;
}