#pragma once

#include "box2d/box2d.h"
#include "nlohmann/json.hpp"
#include "../types/vectors.h"

void to_json(nlohmann::json& j, const b2Vec2& t);

void from_json(const nlohmann::json& j, b2Vec2& t);

void to_json(nlohmann::json& j, const Vec2f& t);

void from_json(const nlohmann::json& j, Vec2f& t);

void to_json(nlohmann::json& j, const Vec3f& t);

void from_json(const nlohmann::json& j, Vec3f& t);