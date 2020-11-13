#include "player.h"

player::player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 1;

	body.setSize(Vector2f(71.11f, 120.0f));
	body.setOrigin(body.getSize() / 2.f);
	body.setPosition(0.0f, 0.0f);
	body.setTexture(texture);
}

player::~player()
{
}

void player::update(float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);

	//walk
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		movement.y -= speed * deltaTime;
		direction = 'u';
		row = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		movement.y += speed * deltaTime;
		direction = 'd';
		row = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		movement.x -= speed * deltaTime;
		direction = 'l';
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		movement.x += speed * deltaTime;
		direction = 'r';
		row = 7;
	}

	if (row == 1 && movement.y == 0) row = 0;
	if (row == 3 && movement.y == 0) row = 2;
	if (row == 5 && movement.x == 0) row = 4;
	if (row == 7 && movement.x == 0) row = 6;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void player::draw(RenderWindow& window)
{
	window.draw(body);
}