#pragma once
#include "stdfn.h"
#include "random.h"
#include "animation.h"
#include "collider.h"

class enemy
{
public:
	char direction = '.';
	enemy(Texture* texture, Vector2u imageCount, Vector2f size, Vector2f position, float switchTime, float speed);
	~enemy();

	void updateStill(float deltaTime);
	void updateFly(float deltaTime, Vector2f playerPosition);
	void updateWalk();
	void updateSemiBoss();
	void updateBoss(float deltaTime);
	void draw(RenderWindow& window);
	void setPosition(sf::Vector2f(xy)) { body.setPosition(xy); };

	Vector2f getPosition() { return body.getPosition(); }

private:
	RectangleShape body;
	animation animation;
	Vector2f size;
	Vector2f position;
	unsigned int row;
	float speed = 20;
};