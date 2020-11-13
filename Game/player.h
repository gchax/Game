#pragma once
#include "stdfn.h"
#include "animation.h"
#include "collider.h"
#include "projectile.h"

class player
{
public:
	char direction = '.';
	player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	~player();

	void update(float deltaTime);
	void draw(RenderWindow& window);
	void setPosition(sf::Vector2f(xy)) { body.setPosition(xy); };
	void setSize(sf::Vector2f(x)) { body.setSize(x); };

	Vector2f getPosition() { return body.getPosition(); }
	collider getCollider() { return collider(body); }

private:
	RectangleShape body;
	animation animation;
	unsigned int row;
	float speed;
};