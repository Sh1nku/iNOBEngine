#include "animationsystem.h"
#include "../component.h"
#include "../gameobject.h"
#include "../components/animation.h"

AnimationSystem::AnimationSystem() {
	mName = "AnimationSystem";
	mMap.insert({ Component::GetBitcode("Animation"), std::make_unique<gameObject_map>() });
}

void AnimationSystem::Update(float dt) {
	for (auto& entry : *GetEntries(Component::GetBitcode("Animation"))) {
		if (entry.first->active) {
			Animation* animation = (Animation*)entry.second->at(Component::GetBitcode("Animation"));
			AnimationClip* clip = animation->currentClip;
			animation->timeSinceLastUpdate += dt;
			if (((float)clip->frames[animation->currentFrame].length) / frameRate < animation->timeSinceLastUpdate) {
				if ((clip->frames.size() - 1) > animation->currentFrame) {
					animation->currentFrame++;
					animation->timeSinceLastUpdate = 0;
				}
				else {
					if (clip->looping) {
						animation->currentFrame = 0;
						animation->timeSinceLastUpdate = 0;
					}
					else {
						animation->FireEvent(animation->currentClip->name, nullptr);
					}
				}
			}
		}
	}
}