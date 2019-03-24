#include "testsystem.h"
#include "../components/testcomponent.h"


TestSystem::TestSystem() {
	mMap.insert({ Component::TYPE::TEST_COMPONENT, new  std::unordered_map<GameObject*, std::unordered_map<UI32,Component*>*> });
}

TestSystem::~TestSystem() {

}

void TestSystem::Update(float dt) {
	mMap.at(Component::TEST_COMPONENT);
	for (auto entry : *GetEntries(Component::TEST_COMPONENT)) {
		TestComponent* comp = (TestComponent*) entry.second->at(Component::TEST_COMPONENT);
		comp->value += 1;
	}
}