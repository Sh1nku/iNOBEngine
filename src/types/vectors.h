#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

using Vec2f = glm::vec2;
using Vec3f = glm::vec3;

Vec2f b2Vec2ToVec2f(b2Vec2 vec);
Vec3f b2Vec2ToVec3f(b2Vec2 vec);

b2Vec2 Vec2fToB2Vec2(Vec2f vec);
b2Vec2 Vec3fToB2Vec2(Vec3f vec);


b2Vec2 GetVector(b2Vec2 v1, b2Vec2 v2);