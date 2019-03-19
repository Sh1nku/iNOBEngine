#include "component.h"
#include "gameobject.h"


Component::Component(GameObject *parent) {
	this->mParent = parent;
}


Component::~Component()
{
}

GameObject *Component::GetParent(){
	return mParent;
}
