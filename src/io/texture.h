#pragma once
#include "../types/enginetypes.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "../types/vectors.h"

class Texture {
public:
	friend class RenderSystem;
	Texture();
	Texture(UI32 id, UI32 width, UI32 height, UI32 comp);
	static Texture* LoadTexture(std::string& name);
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

struct AnimationCoords
{
	AnimationCoords(float topLeftX, float topLeftY, float bottomRightX, float bottomRightY) :
		topLeft(topLeftX, topLeftY),
		topRight(topLeftX + bottomRightX, topLeftY),
		bottomRight(topLeftX + bottomRightX, topLeftY + bottomRightY),
		bottomLeft(topLeftX, topLeftY + bottomRightY) {}
	Vec2f topLeft, topRight, bottomRight, bottomLeft;
};

struct AnimationFrame
{
	AnimationFrame(AnimationCoords coords, int length) : length(length), coords(coords), currentDuration(0) {}
	AnimationFrame() : length(0), coords(AnimationCoords(0,0,0,0)), currentDuration(0) {}
	int length;
	int currentDuration;
	AnimationCoords coords;
};

struct AnimationClip
{
	void AddFrame(AnimationFrame frame);
	std::vector<AnimationFrame> frames;
	Texture* texture;
	bool looping;
	std::string name;
	AnimationClip(bool looping, Texture* texture) :  looping(looping) {}
	AnimationClip() : looping(false), texture(nullptr) {}
};

void to_json(nlohmann::json& j, const AnimationFrame& t);
void from_json(const nlohmann::json& j, AnimationFrame& t);

void to_json(nlohmann::json& j, const AnimationClip& t);
void from_json(const nlohmann::json& j, AnimationClip& t);