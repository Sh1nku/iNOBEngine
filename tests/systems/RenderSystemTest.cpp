#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(RenderSystemTest, CreateRenderSystem_DEPENDS_UI) {
	Manager* manager = Manager::GetInstance();
	RenderSystem* renderSystem = new RenderSystem();
	manager->AddSystem((SystemProgram*)renderSystem);
	RenderSystem* renderSystem2 = manager->GetSystem<RenderSystem>();
	ASSERT_EQ(renderSystem, renderSystem2);
	delete manager;
}

TEST(RenderSystemTest, ShowFromComponent_DEPENDS_UI) {
	RenderSystem renderSystem;
	GameObject obj;
	obj.AddComponent(new Animation());
	obj.AddComponent(new Transform());
	renderSystem.AddToSystem(&obj);
	renderSystem.Update(0);
	SDL_Delay(1000);
}