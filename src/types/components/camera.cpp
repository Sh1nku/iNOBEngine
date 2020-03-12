#include "camera.h"
#include "../../eventmanager.h"
#include "../../manager.h"

Component* Camera::Clone(GameObject* parent) {
	Camera* camera = new Camera();
	camera->mParent = parent;
	camera->type = type;
	camera->fov = fov;
	camera->zNear = zNear;
	camera->zFar = zFar;
	Manager::GetInstance()->eventManager.FireEvent("CHANGE_PERSPECTIVE", new std::tuple(std::make_tuple(type, fov, zNear, zFar)));
	return camera;
}

UI32 Camera::GetBitcode() {
	static UI32 bitcode = bitcodes.at("Camera");
	return bitcode;
}

const auto x = [&] {
	AddComponentToList<Camera>("Camera");
	return true;
}();

CAMERA_TYPE Camera::GetTypeFromString(std::string type) {
	if (type == "orthographic") {
		return ORTHOGRAPHIC;
	}
	else {
		return PERSPECTIVE;
	}
}

void to_json(nlohmann::json& j, const Camera& t) {
	j = nlohmann::json{ {"name", "Camera"}, {"type", } };
}

void from_json(const nlohmann::json& j, Camera& t) {
	auto& type = j.find("type");
	if (type != j.end()) {
		t.type = Camera::GetTypeFromString(type.value());
	}
	auto& fov = j.find("fov");
	if (fov != j.end()) {
		t.fov = fov.value();
	}
	auto& zNear = j.find("zNear");
	if (zNear != j.end()) {
		t.zNear = zNear.value();
	}
	auto& zFar = j.find("zFar");
	if (zFar != j.end()) {
		t.zFar = zFar.value();
	}
	Manager::GetInstance()->eventManager.FireEvent("CHANGE_PERSPECTIVE", new std::tuple(std::make_tuple(t.type, t.fov, t.zNear, t.zFar)));
}