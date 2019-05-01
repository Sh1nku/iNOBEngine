#include "scriptsystem.h"
#include "../components/scriptcomponent.h"
#include "../../io/luaimplementation.h"

ScriptSystem::ScriptSystem() {
	mMap.insert({ Component::GetBitcode("ScriptComponent"), std::make_unique<gameObject_map>() });
	LuaImplementation::Init();
}

ScriptSystem::~ScriptSystem() {
	LuaImplementation::Destroy();
}

void ScriptSystem::Update(float dt) {
	for (auto& entry : *GetEntries(Component::GetBitcode("ScriptComponent"))) {
		ScriptComponent* script = (ScriptComponent*)entry.second->at(Component::GetBitcode("ScriptComponent"));
		script->DoUpdate(dt);
	}
}