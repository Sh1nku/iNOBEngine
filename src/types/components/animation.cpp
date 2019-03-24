#include "animation.h"

Component::TYPE Animation::GetBitcode() {
	return Component::TYPE::ANIMATION;
}

void to_json(nlohmann::json& j, const Animation& t) {

}

void from_json(const nlohmann::json& j, Animation& t) {

}