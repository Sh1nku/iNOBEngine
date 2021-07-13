#pragma once
#include "../component.h"
#include "../../io/texture.h"
#include "box2d/box2d.h"

enum ANIMATION_STATES {
	STARTED,
	FINISHED
};

class AnimationSystem;

class Animation : public Component {
public:
	friend class AnimationSystem;
	Animation(GameObject *parent = nullptr);
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	void SetClip(const std::string& name, bool restartIfAlready = true);
	void SetColor(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
	const std::tuple<float, float, float, float>& GetColor();

	AnimationClip* currentClip;
	int currentFrame;
	void Subscribe(std::string clip, ANIMATION_STATES state, void (*function)());
protected:
	double timeSinceLastUpdate = 0;
private:
	void FireEvent(std::string& clip, ANIMATION_STATES state);
	std::unordered_map<std::string, std::unordered_map<ANIMATION_STATES, std::vector<void(*)()>>> events;
	std::tuple<float,float,float,float> mColor;

};

void to_json(nlohmann::json& j, const Animation& t);
void from_json(const nlohmann::json& j, Animation& t);