#include "mapstate.h"

mapstate::mapstate(Texture* texture, Vector2f position, Vector2f size)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

mapstate::~mapstate()
{
}

void mapstate::draw(RenderWindow& window)
{
	window.draw(body);
}
