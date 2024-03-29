#include "animation.h"
#include "../gameobject.h"
#include "../component.h"
#include "../../io/resources.h"

Animation::Animation(GameObject *parent) : Component(parent), currentFrame(0), mColor(1,1,1,1) {
	currentClip = Resources::GetClip("error_clip");
}

Component* Animation::Clone(GameObject* parent) {
	Animation* anim = new Animation();
	anim->mParent = parent;
	anim->currentClip = currentClip;
	anim->currentFrame = currentFrame;
	return anim;
}

UI32 Animation::GetBitcode() {
	static UI32 bitcode = Component::GetBitcode("Animation");
	return bitcode;
}

const auto x = [] {
	AddComponentToList<Animation>("Animation");
	return true;
}();

void to_json(nlohmann::json& j, const Animation& t) {
	j = nlohmann::json{ {"name", "Animation"}};
}

void from_json(const nlohmann::json& j, Animation& t) {
	std::string clip = j.at("default");
	t.SetClip(clip);

	const auto& it = j.find("color");
	if (it != j.end()) {
		std::vector<float> vector;
		it.value().get_to(vector);
		t.SetColor(vector[0], vector[1], vector[2], vector[3]);
	}
}

void Animation::SetClip(const std::string& clip, bool restartIfAlready) {
	AnimationClip* newClip = Resources::GetClip(clip);
	if (currentClip != nullptr) {
		if (currentClip->name == newClip->name && !restartIfAlready) {
			return;
		}
	}
	currentClip = Resources::GetClip(clip);
	currentFrame = 0;
}

const std::string& Animation::GetClip()
{
	return currentClip->name;
}

void Animation::SetColor(float r, float g, float b, float a)
{
	std::get<0>(mColor) = r;
	std::get<1>(mColor) = g;
	std::get<2>(mColor) = b;
	std::get<3>(mColor) = a;
}

const std::tuple<float, float, float, float>& Animation::GetColor()
{
	return mColor;
}