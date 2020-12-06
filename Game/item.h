#pragma once
#include "stdfn.h"
#include "animation.h"

class item
{
public:
	bool isPickedUp = false;
	bool isCoin = false;
	RectangleShape body;

	item(Texture* texture, Vector2u imageCount, Vector2f size);
	void update(float deltaTime);
	void draw(RenderWindow& window);

private:
	animation animation;
	Vector2f size;
};

