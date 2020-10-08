#include "player.h"

player::player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;

	body.setSize(sf::Vector2f(64.0f, 108.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(0.0f, 0.0f);
	body.setTexture(texture);
}

player::~player()
{
}

void player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement.y -= speed * deltaTime;
		row = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y += speed * deltaTime;
		row = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x -= speed * deltaTime;
		row = 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += speed * deltaTime;
		row = 7;
	}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))

	if (row == 1 && movement.y == 0) row = 0;
	if (row == 3 && movement.y == 0) row = 2;
	if (row == 5 && movement.x == 0) row = 4;
	if (row == 7 && movement.x == 0) row = 6;

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}