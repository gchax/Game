#pragma once
#include "stdfn.h"
#include "animation.h"
#include "collider.h"

class player
{
public:
	player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	~player();

	void update(float deltaTime);
	void draw(RenderWindow& window);

	Vector2f getPosition() { return body.getPosition(); }
	collider getCollider() { return collider(body); }

private:
	RectangleShape body;
	animation animation;
	unsigned int row;
	float speed;
};

