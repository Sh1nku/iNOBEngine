#pragma once
#include "types\enginetypes.h"
#include <iostream>

class Texture {
public:
	Texture();
	Texture(UI32 id, UI32 width, UI32 height, UI32 comp);
	static Texture* LoadTexture(std::string name);
	UI32 GetID();
	UI32 GetWidth();
	UI32 GetHeight();
	UI32 GetComp();
private:
	UI32 id;
	UI32 width;
	UI32 height;
	UI32 comp;
};