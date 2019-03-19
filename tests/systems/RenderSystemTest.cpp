#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(RenderSystemTest, CreateRenderSystem) {
	Manager* manager = Manager::GetInstance();
	RenderSystem* renderSystem = new RenderSystem();
	manager->AddSystem((SystemProgram*) renderSystem);
	RenderSystem* renderSystem2 = manager->GetSystem<RenderSystem>();
	ASSERT_EQ(renderSystem,renderSystem2);
	delete manager;
}