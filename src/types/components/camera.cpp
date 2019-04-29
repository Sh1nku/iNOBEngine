#include "camera.h"

Component* Camera::Clone(GameObject* parent) {
	Camera* camera = new Camera();
	camera->mParent = mParent;
	return camera;
}

UI32 Camera::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Camera");
	return bitcode;
}

const auto x = [&] {
	Component::AddBitcode("Camera");
	jsonComponentList.emplace("Camera", &CreateComponent<Camera>);
	return true;
}();

void to_json(nlohmann::json& j, const Camera& t) {
	j = nlohmann::json{ {"name", "Camera"} };
}

void from_json(const nlohmann::json& j, Camera& t) {
	t;
}