#pragma once
#include "stdfn.h"
#include "collider.h"
#include "player.h"

class hitbox
{
public:
	hitbox(Vector2f* position, Vector2f size);
	~hitbox();

	void update();
	void draw(RenderWindow& window);
	bool checkCollider(const FloatRect& frect);
	void setPosition(sf::Vector2f(xy)) { box.setPosition(xy); };

	Vector2f getPosition() { return box.getPosition(); }
	collider getCollider() { return collider(box); }

private:
	RectangleShape box;
	Vector2f size;
	Vector2f position;
};