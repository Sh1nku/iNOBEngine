#include "systemprogram.h"
#include "component.h"
#include "gameobject.h"


SystemProgram::SystemProgram() {
	mName = "Not Defined";
}


SystemProgram::~SystemProgram() {

}

void SystemProgram::Update(float dt) {

}

void SystemProgram::AddToSystem(GameObject* obj) {
	for (auto& thing : mMap) {
		if ((thing.first & obj->GetComponentEnum()) == thing.first) {
			auto componentMap = std::make_unique<std::unordered_map<UI32, Component*>>();
			for (auto& comp : obj->mComponents) {
				if (comp.first & thing.first) {
					componentMap->emplace(comp);
				}
			}
			thing.second->emplace(obj,std::move(componentMap));
		}
	}
}

void SystemProgram::RemoveFromSystem(UI32 id, GameObject* obj) {
	for (auto& ref : mMap) {
		ref.second->erase(obj);
	}
}

gameObject_map* SystemProgram::GetEntries(UI32 bitcode) {
	return mMap.at(bitcode).get();
}

const std::string& SystemProgram::GetName()
{
	return mName;
}
