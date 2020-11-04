#pragma once
#include "stdfn.h"
#include "collider.h"

class themap
{
public:
	themap(Texture* texture, Vector2f position, Vector2f size);
	~themap();

	void draw(RenderWindow& window);
	collider getCollider() { return collider(body); }

private:
	RectangleShape body;
};
