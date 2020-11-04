#pragma once
#include "stdfn.h"
#include "collider.h"

class mapstate
{
public:
	mapstate(Texture* texture, Vector2f position, Vector2f size);
	~mapstate();

	void draw(RenderWindow& window);
	collider getCollider() { return collider(body); }

private:
	RectangleShape body;
};
