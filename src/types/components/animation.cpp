#include "animation.h"

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

}

void from_json(const nlohmann::json& j, Animation& t) {

}