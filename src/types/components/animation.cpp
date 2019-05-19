#include "animation.h"
#include "../gameobject.h"
#include "../component.h"
#include "../../io/resources.h"

Animation::Animation(GameObject *parent) : Component(parent), currentFrame(0) {
	currentClip = Resources::GetClip(std::string("error_clip"));
}

Component* Animation::Clone(GameObject* parent) {
	Animation* anim = new Animation();
	anim->mParent = parent;
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

void Animation::SetClip(std::string& clip, bool restartIfAlready) {
	AnimationClip* newClip = Resources::GetClip(clip);
	if (currentClip != nullptr) {
		if (currentClip->name == newClip->name && !restartIfAlready) {
			return;
		}
	}
	currentClip = Resources::GetClip(clip);
	currentFrame = 0;
}

void Animation::Subscribe(std::string clip, ANIMATION_STATES state, void(*function)()) {
	auto& clipEvent = events.find(clip);
	if (clipEvent != events.end()) {
		auto& stateEvent = clipEvent->second.find(state);
		if (stateEvent != clipEvent->second.end()) {
			stateEvent->second.emplace_back(function);
		}
		else {
			clipEvent->second.emplace(state, std::vector<void(*)()>());
			clipEvent->second.at(state).emplace_back(function);
		}
	}
	else {
		events.emplace(clip, std::unordered_map<ANIMATION_STATES, std::vector<void(*)()>>());
		events.at(clip).emplace(state, std::vector<void(*)()>());
		events.at(clip).at(state).emplace_back(function);
	}
}

void Animation::FireEvent(std::string& clip, ANIMATION_STATES state) {
	auto& clipEvent = events.find(clip);
	if (clipEvent != events.end()) {
		auto& stateEvent = clipEvent->second.find(state);
		if (stateEvent != clipEvent->second.end()) {
			for (auto& func : stateEvent->second) {
				func();
			}
		}
	}
}