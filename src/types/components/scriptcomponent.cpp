#include "scriptcomponent.h"
#include "../script.h"
#include "../../io/resources.h"

Script& ScriptComponent::AddScript(Script& script) {
	return scripts.emplace_back(Script(script));
}

void ScriptComponent::DoUpdate(float dt) {
	for (auto& script : scripts) {
		if (script.started != true) {
			script.SetGameObject(GetParent());
			script.Start();
			script.started = true;
		}
		script.Update(dt);
	}
}

Component* ScriptComponent::Clone(GameObject* parent) {
	ScriptComponent* component = new ScriptComponent();
	component->mParent = parent;
	for (auto& script : scripts) {
		component->AddScript(script);
	}
	return component;
}

UI32 ScriptComponent::GetBitcode() {
	static UI32 bitcode = Component::GetBitcode("ScriptComponent");
	return bitcode;
}

const auto x = [] {
	AddComponentToList<ScriptComponent>("ScriptComponent");
	return true;
}();

void to_json(nlohmann::json& j, const ScriptComponent& c) {

}

void from_json(const nlohmann::json& j, ScriptComponent& c) {
	std::vector<std::string> tempScripts;
	j.at("scripts").get_to(tempScripts);
	for (auto& script : tempScripts) {
		auto& ref = c.AddScript(*Resources::GetScript(script));
	}
}