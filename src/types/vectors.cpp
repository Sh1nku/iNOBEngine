#include "vectors.h"

b2Vec2 GetVector(b2Vec2 v1, b2Vec2 v2) {
	b2Vec2 retVec;
	retVec.x = v2.x - v1.x;
	retVec.y = v2.y - v1.x;
	return retVec;
}
