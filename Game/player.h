#pragma once
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "collider.h"

class player
{
public:
	player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() { return body.getPosition(); }
	collider getCollider() { return collider(body); }

private:
	sf::RectangleShape body;
	animation animation;
	unsigned int row;
	float speed;
};

