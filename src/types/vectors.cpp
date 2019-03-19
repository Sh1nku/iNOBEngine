#include "vectors.h"
#include <cmath>

float Vector2f::getLength(Vector3f* v) {
	return sqrt(pow(v->x, 2) + pow(v->y, 2));
}

Vector3f toVector3(Vector2f* v) {
	return Vector3f(v->x, v->y, 0);
}