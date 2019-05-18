#include "collisiondebugdraw.h"
#include <SDL_opengl.h>
#include <gl\GLU.h>

void CollisionDebugDraw::DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBegin(GL_LINE_LOOP);
	glColor4f(color.r, color.g, color.b, color.a);
	for (int i = 0; i < vertexCount; i++) {
		glVertex3f(vertices[i].x, vertices[i].y, 0);
	}
	glEnd();
	glPopMatrix();
}

void CollisionDebugDraw::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(color.r, color.g, color.b, color.a);
	for (int i = 0; i < vertexCount; i++) {
		glVertex3f(vertices[i].x, vertices[i].y, 0);
	}
	glEnd();
	glPopMatrix();
}

void CollisionDebugDraw::DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color)
{
	int i = 0;
}

void CollisionDebugDraw::DrawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis, const b2Color & color)
{
	int i = 0;
}

void CollisionDebugDraw::DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color)
{
	int i = 0;
}

void CollisionDebugDraw::DrawTransform(const b2Transform & xf)
{
	int i = 0;
}

void CollisionDebugDraw::DrawPoint(const b2Vec2 & p, float32 size, const b2Color & color)
{
	int i = 0;
}
