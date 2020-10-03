#include <SFML\Graphics.hpp>
#include <iostream>
#include "player.h"

static const float VIEW_HEIGHT = 650.0f;

void resizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Jack!", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("test.png");

	player player(&playerTexture, sf::Vector2u(8, 6), 0.15f, 196.0f);
		
	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evt;
		while (window.pollEvent(evt)) 
		{
			switch (evt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				resizeView(window, view);
				break;
			}
		}

		player.Update(deltaTime);
		//view.setCenter(player.getPosition());

		window.clear(sf::Color(110, 150, 150));
		window.setView(view);
		player.Draw(window);
		window.display();
	}

	return 0;
}