#pragma once
#include "stdfn.h"

class collider
{
public:
	collider(RectangleShape& body);
	~collider();

	void move(float dx, float dy) { body.move(dx, dy); }

	bool checkCollider(collider other, float push);
	Vector2f getPosition() { return body.getPosition(); }
	Vector2f getHalfSize() { return body.getSize() / 2.0f; }

private:
	RectangleShape& body;
};