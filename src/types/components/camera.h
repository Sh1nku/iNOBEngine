#pragma once
#include "../component.h"

enum CAMERA_TYPE {
	ORTHOGRAPHIC,
	PERSPECTIVE
};

class Camera : public Component {
public:
	Camera(GameObject *parent = nullptr) : Component(parent), type(PERSPECTIVE), fov(45), zNear(0), zFar(100) { }
	Component* Clone(GameObject* parent) override;
	UI32 GetBitcode() override;
	static CAMERA_TYPE GetTypeFromString(std::string type);
	CAMERA_TYPE GetType();

	CAMERA_TYPE type;
	UI16 fov;
	float zNear;
	float zFar;

private:
};

void to_json(nlohmann::json& j, const Camera& t);
void from_json(const nlohmann::json& j, Camera& t);