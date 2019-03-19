struct Vector2f;
struct Vector3f;

struct Vector2f
{
public:
	Vector2f() : x(0), y(0) {};
	Vector2f(float x, float y) : x(x),y(y) {};

	static float getLength(Vector3f* v);
	static Vector3f toVector3(Vector2f* v);

	float x, y;
};

struct Vector3f
{
public:
	Vector3f() : x(0), y(0), z(0) {};
	Vector3f(float x, float y, float z) : x(x),y(y), z(z) {};
	float x, y, z;
};