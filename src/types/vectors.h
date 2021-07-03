#pragma once
#include <box2d/box2d.h>
#include <glm/glm.hpp>

using Vec2f = glm::vec2;
using Vec3f = glm::vec3;

Vec2f b2Vec2ToVec2f(b2Vec2 vec);
Vec3f b2Vec2ToVec3f(b2Vec2 vec);

b2Vec2 Vec2fToB2Vec2(Vec2f vec);
b2Vec2 Vec3fToB2Vec2(Vec3f vec);


Vec2f GetVector2f(Vec2f v1, Vec2f v2);
Vec2f GetVector3f(Vec3f v1, Vec3f v2);