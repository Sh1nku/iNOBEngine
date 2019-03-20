#include "texture.h"

Texture::Texture() {

}

Texture::Texture(UI32 id, UI32 width, UI32 height, UI32 comp) : id(id), width(width), height(height), comp(comp) {

}

Texture* loadTexture(std::string name) {
	return new Texture();
}

UI32 Texture::GetID() {
	return id;
}

UI32 Texture::GetWidth() {
	return width;
}

UI32 Texture::GetHeight() {
	return height;
}

UI32 Texture::GetComp() {
	return comp;
}