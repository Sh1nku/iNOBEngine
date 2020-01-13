#include "vectors.h"

Vec2f b2Vec2ToVec2f(b2Vec2 vec)
{
	return Vec2f(vec.x, vec.y);
}

Vec3f b2Vec2ToVec3f(b2Vec2 vec)
{
	return Vec3f(vec.x, vec.y, 0);
}

b2Vec2 Vec2fToB2Vec2(Vec2f vec)
{
	return b2Vec2(vec.x, vec.y);
}

b2Vec2 Vec3fToB2Vec2(Vec3f vec)
{
	return b2Vec2(vec.x, vec.y);
}

b2Vec2 GetVector(b2Vec2 v1, b2Vec2 v2) {
	b2Vec2 retVec;
	retVec.x = v2.x - v1.x;
	retVec.y = v2.y - v1.x;
	return retVec;
}
