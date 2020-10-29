#include "player.h"

player::player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 2;

	body.setSize(Vector2f(50.0f, 75.0f));
	body.setOrigin(body.getSize() / 2.0f);
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
		row = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		movement.y += speed * deltaTime;
		row = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		movement.x -= speed * deltaTime;
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		movement.x += speed * deltaTime;
		row = 7;
	}/*
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D))
	{
		row = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D))
	{
		row = 3;
	}*/
	//run
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.y -= (speed * deltaTime) / 2.5f;
		row = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.y += (speed * deltaTime) / 2.5f;
		row = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.x -= (speed * deltaTime) / 2.5f;
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.x += (speed * deltaTime) / 2.5f;
		row = 7;
	}/*
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		row = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		row = 3;
	}*/
	////hit
	//if (Keyboard::isKeyPressed(Keyboard::Space))

	if (row == 1 && movement.y == 0) row = 0;
	if (row == 3 && movement.y == 0) row = 2;
	if (row == 5 && movement.x == 0) row = 4;
	if (row == 7 && movement.x == 0) row = 6;

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void player::draw(RenderWindow& window)
{
	window.draw(body);
}