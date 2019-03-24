#include "testsystem.h"
#include "../components/testcomponent.h"


TestSystem::TestSystem() {
	mMap.insert({ Component::TYPE::TEST_COMPONENT, std::make_unique<gameObject_map>() });
	mMap.insert({ Component::TYPE::TEST_COMPONENT | Component::TYPE::TRANSFORM, std::make_unique<gameObject_map>() });
}

TestSystem::~TestSystem() {

}

void TestSystem::Update(float dt) {
	for (auto& entry : *GetEntries(Component::TEST_COMPONENT)) {
		TestComponent* comp = (TestComponent*) entry.second->at(Component::TEST_COMPONENT);
		comp->value += 1;
	}
	for (auto& entry : *GetEntries(Component::TEST_COMPONENT | Component::TRANSFORM)) {
		TestComponent* comp = (TestComponent*)entry.second->at(Component::TEST_COMPONENT);
		comp->value += 1;
	}
	try {
		for (auto& entry : *GetEntries(Component::TRANSFORM)) {
			//Should not run
				TestComponent* comp = (TestComponent*)entry.second->at(Component::TEST_COMPONENT);
				comp->value += 1;
			}
	}
	catch (const std::exception&) {

	}
}