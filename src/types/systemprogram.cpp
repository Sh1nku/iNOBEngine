#include "systemprogram.h"



SystemProgram::SystemProgram()
{
}


SystemProgram::~SystemProgram()
{
}

void SystemProgram::Update(float dt) {

}

std::vector<std::vector<Component*>*>* SystemProgram::GetEntries(UI32 bitcode) {
	return mMap.at(bitcode);
}