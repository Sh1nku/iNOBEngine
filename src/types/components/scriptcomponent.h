#pragma once
#include "../component.h"
#include "../script.h"

class ScriptComponent : public Component {
public:
	ScriptComponent(GameObject *parent = nullptr) : Component(parent) {};
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	Script& AddScript(Script& script);
	void DoUpdate(float dt);
private:
	std::vector<Script> scripts;
};