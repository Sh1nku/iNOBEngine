#include "component.h"
#include "gameobject.h"
#include "types/components/testcomponent.h"
#include "types/components/transform.h"

mapType jsonComponentList = {
	{"TestComponent" , &CreateComponent<TestComponent>},
	{"Transform" , &CreateComponent<Transform>}
};

Component::Component(GameObject *parent) {
	this->mParent = parent;
}


Component::~Component()
{
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