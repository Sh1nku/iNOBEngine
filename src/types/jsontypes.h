#pragma once

#include "Box2D/Box2D.h"
#include "nlohmann/json.hpp"

void to_json(nlohmann::json& j, const b2Vec2& t);

void from_json(const nlohmann::json& j, b2Vec2& t);