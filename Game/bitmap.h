#pragma once
#include "stdfn.h"
#include "collider.h"

class bitmap
{
public:
	bitmap(Texture* texture, Vector2f position, Vector2f size);
	~bitmap();

	void draw(RenderWindow& window);
	collider getCollider() { return collider(body); }

private:
	RectangleShape body;
};
