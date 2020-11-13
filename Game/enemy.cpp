#include "enemy.h"

enemy::enemy(Texture* texture, Vector2u imageCount, Vector2f size, Vector2f position, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->size = size;
	this->position = position;
	this->speed = speed;
	row = 0;

	body.setSize(size);
	body.setPosition(position);
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.f);
}

enemy::~enemy()
{
}

void enemy::updateStill(float deltaTime)
{
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
}

	Vector2f movement(0.0f, 0.0f);

void enemy::updateFly(float deltaTime, Vector2f playerPosition)
{
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.setPosition(position.x, playerPosition.y);
	//body.setPosition(position.x, playerPosition.y);
}

void enemy::draw(RenderWindow& window)
{
	window.draw(body);
}