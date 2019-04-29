#include "animation.h"
#include "../gameobject.h"
#include "../component.h"
#include "../../io/resources.h"

Animation::Animation(GameObject *parent) : Component(parent), currentFrame(0) {
	currentClip = Resources::GetClip(std::string("error_clip"));
}

Component* Animation::Clone(GameObject* parent) {
	Animation* anim = new Animation();
	anim->mParent = mParent;
	anim->currentClip = currentClip;
	anim->currentFrame = currentFrame;
	return anim;
}

UI32 Animation::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Animation");
	return bitcode;
}

const auto x = [&] {
	Component::AddBitcode("Animation");
	jsonComponentList.emplace("Animation", &CreateComponent<Animation>);
	return true;
}();

void to_json(nlohmann::json& j, const Animation& t) {
	j = nlohmann::json{ {"name", "Animation"}};
}

void from_json(const nlohmann::json& j, Animation& t) {
	std::string clip = j.at("default");
	t.SetClip(clip);
}

void Animation::SetClip(std::string& clip) {
	currentClip = Resources::GetClip(clip);
	currentFrame = 0;
}