#include "component.h"
#include "gameobject.h"

mapType jsonComponentList;
std::unordered_map< std::string, UI32> bitcodes;

Component::Component(GameObject *parent) {
	this->mParent = parent;
}


Component::~Component()
{
}

void Component::AddBitcode(std::string name) {
	static UI32 code = 0;
	bitcodes.emplace(name, 1 << code++);
}

GameObject *Component::GetParent(){
	return mParent;
}

Component* Component::GetComponentFromJson(nlohmann::json &json) {
	return jsonComponentList[json.at("name")](json);
}

void Component::SetParent(GameObject *parent) {
	mParent = parent;
}

UI32 Component::GetBitcode(std::string name) {
	return bitcodes.at(name);
}

