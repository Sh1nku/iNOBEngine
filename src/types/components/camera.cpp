#include "camera.h"

Component::TYPE Camera::GetBitcode() {
	return Component::TYPE::CAMERA;
}

void to_json(nlohmann::json& j, const Camera& t) {

}

void from_json(const nlohmann::json& j, Camera& t) {

}