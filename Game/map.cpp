#include "map.h"

themap::themap(Texture* texture, Vector2f position, Vector2f size)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

themap::~themap()
{
}

void themap::draw(RenderWindow& window)
{
	window.draw(body);
}
