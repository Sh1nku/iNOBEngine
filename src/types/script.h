#pragma once
#include <sol.hpp>
class GameObject;

class Script {
public:
	friend class ScriptComponent;
	Script(std::string text);
	~Script();
	Script(const Script&);
	void Start();
	void Update(float dt);
	void SetGameObject(GameObject* obj);
private:
	sol::environment *env;
	std::string text;
	bool started;
};