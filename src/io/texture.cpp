#include "texture.h"
#include "resources.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "../window/window.h"

Texture::Texture() {

}

Texture::Texture(UI32 id, UI32 width, UI32 height, UI32 comp) : id(id), width(width), height(height), comp(comp) {

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

Texture* Texture::LoadTexture(std::string& file) {
	if (Window::mWindow == nullptr) {
		Texture* retTex = new Texture();
		Resources::textureBacklog.emplace_back(std::make_pair(file, retTex));
		return retTex;
	}
	else {
		SDL_Surface* tempSurface = IMG_Load((Resources::gameDir + file).c_str());
		if (tempSurface == nullptr) {
			std::cout << "Could not load texture: " << file.c_str() << "\n" << IMG_GetError() << std::endl;
			tempSurface = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0);
			SDL_LockSurface(tempSurface);
			Uint32 *pixels = (Uint32 *)tempSurface->pixels;
			pixels[0 + (0 * tempSurface->w)] = 0x00FF00FF;
			pixels[1 + (0 * tempSurface->w)] = 0x00FF00FF;
			pixels[0 + (1 * tempSurface->w)] = 0x00FF00FF;
			pixels[1 + (1 * tempSurface->w)] = 0x00FF00FF;
			SDL_UnlockSurface(tempSurface);
		}
		GLuint textureHandle;
		glBindTexture(GL_TEXTURE_2D, 0);
		glGenTextures(1, &textureHandle);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
		int mode = GL_RGB;
		if (tempSurface->format->BytesPerPixel == 4) {
			mode = GL_RGBA;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, mode, tempSurface->w, tempSurface->h, 0, mode, GL_UNSIGNED_BYTE, tempSurface->pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
		Texture *tex = new Texture(textureHandle, tempSurface->w, tempSurface->h, tempSurface->format->BytesPerPixel);
		SDL_FreeSurface(tempSurface);
		return tex;
	}
}

void AnimationClip::AddFrame(AnimationFrame frame)
{
	frames.push_back(frame);
}

void to_json(nlohmann::json& j, const AnimationFrame& t) {

}

void from_json(const nlohmann::json& j, AnimationFrame& t) {
	t.length = j.at("length");
	std::vector<UI32> coords;
	j.at("coords").get_to(coords);
	t.coords = AnimationCoords((float)coords[0], (float)coords[1], (float)coords[2], (float)coords[3]);
}

void to_json(nlohmann::json& j, const AnimationClip& t) {

}

void from_json(const nlohmann::json& j, AnimationClip& t) {
	Texture* tex;
	try {
		tex = Resources::textures.at(j.at("texture")).get();
	}
	catch (std::exception) {
		tex = Texture::LoadTexture((std::string) j.at("texture"));
		Resources::textures.insert({ j.at("texture"), std::make_unique<Texture>(*tex) });
	}
	t.texture = tex;
	std::vector<AnimationFrame> frames;
	j.at("frames").get_to(frames);
	t.frames = frames;
	t.name = j.at("name");
	t.looping = j.at("looping");

	Resources::clips.insert({ j.at("name"), std::make_unique<AnimationClip>(t) });
}