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

Vec2f GetVector2f(Vec2f v1, Vec2f v2) {
	Vec2f retVec;
	retVec.x = v2.x - v1.x;
	retVec.y = v2.y - v1.y;
	return retVec;
}

Vec2f GetVector3f(Vec3f v1, Vec3f v2) {
	Vec3f retVec;
	retVec.x = v2.x - v1.x;
	retVec.y = v2.y - v1.y;
	retVec.z = v2.z - v1.z;
	return retVec;
}

