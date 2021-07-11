#include "testsystem.h"
#include "../components/testcomponent.h"
#include "../gameobject.h"


TestSystem::TestSystem() {
	mName = "TestSystem";
	mMap.insert({ Component::GetBitcode("TestComponent"), std::make_unique<gameObject_map>() });
	mMap.insert({ Component::GetBitcode("TestComponent") | Component::GetBitcode("Transform"), std::make_unique<gameObject_map>() });
}

TestSystem::~TestSystem() {

}

void TestSystem::Update(float dt) {
	for (auto& entry : *GetEntries(Component::GetBitcode("TestComponent"))) {
		if (entry.first->active) {
			TestComponent* comp = (TestComponent*)entry.second->at(Component::GetBitcode("TestComponent"));
			comp->value += 1;
		}
	}
	for (auto& entry : *GetEntries(Component::GetBitcode("TestComponent") | Component::GetBitcode("Transform"))) {
		if (entry.first->active) {
			TestComponent* comp = (TestComponent*)entry.second->at(Component::GetBitcode("TestComponent"));
			comp->value += 1;
		}
	}
	try {
		for (auto& entry : *GetEntries(Component::GetBitcode("Transform"))) {
			if (entry.first->active) {
				//Should not run
				TestComponent* comp = (TestComponent*)entry.second->at(Component::GetBitcode("TestComponent"));
				comp->value += 1;
			}
		}
	}
	catch (const std::exception&) {

	}
}