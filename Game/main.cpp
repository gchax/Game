#include <SFML\Graphics.hpp>
#include <iostream>
#include <ctime>
#include "player.h"
#include "platform.h"
#include "bitmap.h"
#include "enemy.h"
#include "button.h"

//set view height;
static float viewheight = 1000;

//resizable view;
void resizeView(const RenderWindow&, View&);

//initialize states;
enum states { MENU = 0, HOME, OUTDOOR, SKY, STORE, CASTLE, GAME_OVER, SCORE, CREDIT };
enum wand_states { UNOBTAINED = 0, REGULAR, KINDA_GOOD, OP };

//main;
int main()
{
	//render window;
	RenderWindow window(VideoMode(1700, 1000), "Jack!", Style::Close | Style::Resize);
	View view(Vector2f(0.0f, 0.0f), Vector2f(viewheight + 700, viewheight));
	window.setFramerateLimit(90);
	srand(time(NULL));


	//initialize font;
	Font font;
	font.loadFromFile("8BitDragon.ttf");


	//initialize player;
	Texture jack;
	jack.loadFromFile("jack.png");
	player player(&jack, Vector2u(8, 8), 0.07f, 500.0f);


	//initialize variables;
	int state = MENU;
	int wandState = UNOBTAINED;
	int coin = 100;
	float hp = 1000;
	float mp = 500;
	int counter = 0;


	//define screen size;
	Vector2u ws = window.getSize();
	Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));


	//declare delta time;
	float deltaTime = 0.0f;
	Clock clock[3];


	//initialzie map variables;
	Texture menubg;
	menubg.loadFromFile("jab.jpg");
	platform background(&menubg, Vector2f(windowSize), Vector2f(windowSize / 2.f));

	Texture homebg;
	homebg.loadFromFile("map_home.png");
	platform background1(&homebg, Vector2f(1800.0f, 2070.0f), Vector2f(900.0f, 1035.f));
	vector<bitmap> blockH;
	int home[23][20] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 }
	};
	for (int mapX = 0; mapX < 20; mapX++)
	{
		for (int mapY = 0; mapY < 23; mapY++)
		{
			if (home[mapY][mapX] == 0)
			{
				bitmap outdoor(nullptr, Vector2f(((mapX) * 90) + 45, ((mapY) * 90) + 45), Vector2f(90.f, 90.f));
				blockH.push_back(outdoor);
			}
		}
	}

	Texture outdoorbg;
	outdoorbg.loadFromFile("map_outdoor.png");
	platform background2(&outdoorbg, Vector2f(4920.0f, 5880.0f), Vector2f(2460.0f, 2940.0f));
	vector<bitmap> blockO;
	int outdoor[49][41] =
	{
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
	};
	for (int mapX = 0; mapX < 41; mapX++)
	{
		for (int mapY = 0; mapY < 49; mapY++)
		{
			if (outdoor[mapY][mapX] == 0)
			{
				bitmap outdoor(nullptr, Vector2f(((mapX) * 120) + 60, ((mapY) * 120) + 60), Vector2f(120.f, 120.f));
				blockO.push_back(outdoor);
			}
		}
	}

	Texture skybg;
	skybg.loadFromFile("map_sky.png");
	platform background3(&skybg, Vector2f(7920.0f, 2640.0f), Vector2f(3960.0f, 1320.0f));
	vector<bitmap> blockS;
	int sky[22][66] =
	{
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  1,  1,  1,  1,  0,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0},
		{0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0},
		{0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0},
		{0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
	};
	for (int mapX = 0; mapX < 66; mapX++)
	{
		for (int mapY = 0; mapY < 22; mapY++)
		{
			if (sky[mapY][mapX] == 0)
			{
				bitmap sky(nullptr, Vector2f(((mapX) * 120) + 60, ((mapY) * 120) + 60), Vector2f(120.f, 120.f));
				blockS.push_back(sky);
			}
		}
	}

	Texture storebg;
	storebg.loadFromFile("");
	//platform background(&storebg, Vector2f(), Vector2f(0.f, 0.f));

	Texture textbox;
	textbox.loadFromFile("textbox.png");
	platform box1(&textbox, Vector2f(1700.f, 380.f), Vector2f(windowSize.x / 2.f, 7.f * windowSize.y / 10.f));

	Texture mapCastle;
	mapCastle.loadFromFile("map_castle.png");
	platform castle(&mapCastle, Vector2f(5242.72f, 1080.0f), Vector2f(0.f, 0.f));
	vector<platform> platforms;
	platforms.push_back(platform(nullptr, Vector2f(5242.72f, 1.f), Vector2f(0.f, 450.f)));



	//initialize warpers;
	RectangleShape warperH;
	warperH.setPosition(Vector2f(1170.f, 2040.f));
	warperH.setSize(Vector2f(180.f, 10.f));

	RectangleShape pickUp;
	pickUp.setPosition(Vector2f(900.f, 1440.f));
	pickUp.setSize(Vector2f(90.f, 10.f));

	RectangleShape warperO[2];
	warperO[0].setPosition(Vector2f(3660.f, 4860.f));
	warperO[0].setSize(Vector2f(120.f, 120.f));
	warperO[1].setPosition(Vector2f(840.f, 300.f));
	warperO[1].setSize(Vector2f(480.f, 120.f));

	RectangleShape warperS[3];
	warperS[0].setPosition(Vector2f(1200.f, 2345.f));
	warperS[0].setSize(Vector2f(240.f, 10.f));
	warperS[1].setPosition(Vector2f(840.f, 1000.f));
	warperS[1].setSize(Vector2f(120.f, 10.f));
	warperS[2].setPosition(Vector2f(5420.f, 1800.f));
	warperS[2].setSize(Vector2f(210.f, 10.f));


	//initialize button variables;
	button startGame(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 60, "START", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	startGame.setTextOutlineColor(Color::Black);
	startGame.setTextOutlineThickness(1.f);
	button score(Vector2f(windowSize.x / 2.f, 4.25f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 60, "SCORE", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	score.setTextOutlineColor(Color::Black);
	score.setTextOutlineThickness(1.f);
	button exitGame(Vector2f(windowSize.x / 2.f, 5.f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 60, "EXIT", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	exitGame.setTextOutlineColor(Color::Black);
	exitGame.setTextOutlineThickness(1.f);

	string what_do_you_want[5] = { "How shall I serve thee, master?","What is it that you desire?","What is the purpose of thy presence?","Want some power-ups?","Ye shall only find good stuff here" };
	string bought[3] = { "Thank you, kind sir!\n    Anything else?", "Anything else?", "  Good choice!\nAnything else?" };
	enum click { IDLE = 0, BOUGHT, BYE };
	int buttonState = IDLE;
	button welcomeText(Vector2f(box1.getPosition().x, box1.getPosition().y + 15.f), Vector2f(windowSize.x, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 55, what_do_you_want[rand() % 5], Color::Black, Color::Black, Color::Black);
	button smallPotion(Vector2f(windowSize.x / 2.f, 2.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		1.f, &font, 35, "Small Potion                                  25", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button mediumPotion(Vector2f(windowSize.x / 2.f, 3.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		1.f, &font, 35, "Medium Potion                                  50", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button greaterPotion(Vector2f(windowSize.x / 2.f, 4.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		1.f, &font, 35, "Greater Potion                                100", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button manaPotion(Vector2f(windowSize.x / 2.f, 5.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		1.f, &font, 35, "Mana Potion                                  35", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button mehWand(Vector2f(windowSize.x / 2.f, 6.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		1.f, &font, 35, "Kinda Good Wand                                700", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button betterWand(Vector2f(windowSize.x / 2.f, 7.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		1.f, &font, 35, "OP Wand                              2000", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button done(Vector2f(windowSize.x / 2.f, 8.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		1.f, &font, 35, "Done.", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button thxText(Vector2f(box1.getPosition().x, box1.getPosition().y + 15.f), Vector2f(2.f * windowSize.x / 3.f, 150.f), Color(186, 186, 186), Color(186, 186, 186), Color(186, 186, 186),
		2.f, &font, 55, bought[rand() % 3], Color::Black, Color::Black, Color::Black);
	button byeText(Vector2f(box1.getPosition().x, box1.getPosition().y + 15.f), Vector2f(4.f * windowSize.x / 5.f, 75.f), Color(186, 186, 186), Color(186, 186, 186), Color(186, 186, 186),
		2.f, &font, 45, "Gladly looking forward to seeing you again, kind sir.", Color::Black, Color::Black, Color::Black);
	button returnToTheGame(Vector2f(box1.getPosition().x + 555.f, box1.getPosition().y + 100.f), Vector2f(windowSize.x / 2.f, 50.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 20, "Return to the game.", Color::Black, Color(69, 69, 69, 255), Color(200, 200, 200, 255));

	button gameOver(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 150, "GAME OVER", Color::Red, Color::Red, Color::Red);
	button scoreState(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 25, "SEE THE SCORE", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button returnToMenu(Vector2f(windowSize.x / 2.f, 5.f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 25, "RETURN TO THE MENU", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

	
	//initialize weapons;
	Texture item;
	item.loadFromFile("sparkle.png");
	platform wand(&item, Vector2f(75.f, 75.f), Vector2f(945.0f, 1400.0f));

	Texture fireball;
	fireball.loadFromFile("fireball.png");
	projectile bullet(&fireball, 10.f, 0.f);
	vector<projectile>::const_iterator bulletIter;
	vector<projectile> projectileArray;


	//initialize enemies;
	Texture gargoyle1;
	gargoyle1.loadFromFile("gargoyle1.png");
	enemy normalGargoyle1(&gargoyle1, Vector2u(5, 1), Vector2f(360.f, 232.f), Vector2f(1080.f, rand() % 500 + 6000), 0.08f, 20.f);

	Texture gargoyle1_5;
	gargoyle1_5.loadFromFile("flippedgargoyle1.png");
	enemy normalGargoyle2(&gargoyle1_5, Vector2u(5, 1), Vector2f(360.f, 232.f), Vector2f(2520.f, 4500.f), 0.08f, 20.f);

	Texture gargoyle2;
	gargoyle2.loadFromFile("gargoyle2.png");
	//enemy normalGargoyle1(&gargoyle2, Vector2u(5, 2), Vector2f(360.f, 232.f), Vector2f(1080.f, rand() % 500 + 6000), 0.08f, 20.f);

	Texture gargoyle2_5;
	gargoyle2_5.loadFromFile("flippedgargoyle2.png");
	//enemy normalGargoyle2(&gargoyle2_5, Vector2u(5, 2), Vector2f(360.f, 232.f), Vector2f(2520.f, 4500.f), 0.08f, 20.f);

	Texture titan1;
	titan1.loadFromFile("titan1.png");
	vector<enemy>::const_iterator titan1Iter;
	vector<enemy> titan1Array;
	enemy normalTitan(&titan1, Vector2u(3, 4), Vector2f(152.f, 200.f), Vector2f(2500.f, 2030.f), 0.04f, 20.f);

	Texture titan2;
	titan2.loadFromFile("titan2.png");
	vector<projectile>::const_iterator titan2Iter;
	vector<projectile> titan2Array;

	Texture monSeller;
	monSeller.loadFromFile("mon_seller.png");
	enemy seller(&monSeller, Vector2u(2, 1), Vector2f(33.f * 16, 49.f * 16), Vector2f(windowSize.x / 2.f + 432.f, windowSize.y / 2.f - 50.f), 0.8, 0.f);


	//game loop;
	while (window.isOpen())
	{
		//call delta time;
		deltaTime = clock[0].restart().asSeconds();

		//initialize time variables;
		Time elapse[3];
		elapse[0] = clock[0].getElapsedTime();
		elapse[1] = clock[1].getElapsedTime();
		elapse[2] = clock[2].getElapsedTime();

		//set window event;
		Event evt;
		while (window.pollEvent(evt)) if (evt.type == Event::Closed) window.close();

		//check coordinate;
		Vector2i pos = Mouse::getPosition(window);
		Vector2f mousePos(static_cast<float>(pos.x), static_cast<float>(pos.y));

		//initialize collider;
		collider playerCollision = player.getCollider();
		collider bulletCollision = bullet.getCollider();

		//player position;
		Vector2f playerPosition = player.getPosition();
		cout << "x = " << player.getPosition().x << " y = " << player.getPosition().y << std::endl;

		//menu;
		if (state == MENU)
		{
			//update buttons;
			startGame.update(mousePos);
			score.update(mousePos);
			exitGame.update(mousePos);

			//set view;
			view.setCenter(windowSize / 2.f);

			//clear screen;
			window.clear();
			window.setView(view);

			//start game;
			if (startGame.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					player.setPosition(Vector2f(1125.0f, 595.0f));
					state = HOME;
				}
			}

			//see scores;
			if (score.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					state = SCORE;
				}
			}

			//exit game;
			if (exitGame.getGlobalBounds().contains(mousePos)) if (Mouse::isButtonPressed(Mouse::Left)) window.close();

			//draw background;
			background.draw(window);

			//draw logo;
			//logo.draw(window);

			//draw buttons
			startGame.draw(window);
			score.draw(window);
			exitGame.draw(window);

			//display window;
			window.display();
		}

		//stage 1;
		if (state == HOME)
		{
			//update entities;
			player.update(deltaTime);

			//map collision;
			for (int i = 0; i < blockH.size(); i++)	blockH[i].getCollider().checkCollider(playerCollision, 1.0f);

			//set view;
			view.setCenter(playerPosition);

			//clear window;
			window.clear(Color(16, 16, 16));
			window.setView(view);

			//draw map texture;
			background1.draw(window);

			//draw items;
			if (wandState == UNOBTAINED) wand.draw(window);

			//draw player;
			player.draw(window);

			//pause;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				//declare screen size;
				Vector2u ws = window.getSize();
				Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));

				//initialize button variables;
				button resume(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 150, "RESUME", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
				button txt(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 25, "PRESS ENTER TO CONTINUE", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

				//menu loop;
				while (window.isOpen())
				{
					Event evt;
					while (window.pollEvent(evt))
					{
						if (evt.type == Event::Closed) window.close();
					}

					view.setCenter(windowSize / 2.f);
					window.clear();
					window.setView(view);

					resume.draw(window);
					txt.draw(window);

					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						break;
					}

					window.display();
				}
			}

			//wand discovery
			if (player.getGlobalBounds().intersects(pickUp.getGlobalBounds()))
			{
				cout << "pick it up";
			}

			//go outside;
			if (player.getGlobalBounds().intersects(warperH.getGlobalBounds()))
			{
				window.clear();
				player.setPosition(Vector2f(3720.0f, 5100.0f));
				state = OUTDOOR;
			}

			//display window;
			window.display();
		}

		//stage 2;
		if (state == OUTDOOR)
		{
			//update entities;
			/*if (player.getPosition().y >= 5000 && player.getPosition().y <= 6500) normalGargoyle1.updateFly(deltaTime, player.getPosition());
			else normalGargoyle1.updateStill(deltaTime);
			normalGargoyle2.updateStill(deltaTime);*/
			player.update(deltaTime);

			//map collision;
			for (int i = 0; i < blockO.size(); i++)	blockO[i].getCollider().checkCollider(playerCollision, 1.0f);

			//set view;
			view.setCenter(player.getPosition());

			//clear screen;
			window.clear(Color(127, 231, 255));
			window.setView(view);

			//draw map texture;
			background2.draw(window);

			//draw entities;
			/*normalGargoyle1.draw(window);
			normalGargoyle2.draw(window);*/
			player.draw(window);

			//pause;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				//declare screen size;
				Vector2u ws = window.getSize();
				Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));

				//initialize button variables;
				button resume(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 150, "RESUME", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
				button txt(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 25, "PRESS ENTER TO CONTINUE", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

				//menu loop;
				while (window.isOpen())
				{
					view.setCenter(windowSize / 2.f);
					window.clear();
					window.setView(view);

					resume.draw(window);
					txt.draw(window);

					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						break;
					}

					window.display();
				}
			}

			//go back inside the house;
			if (player.getGlobalBounds().intersects(warperO[0].getGlobalBounds()))
			{
				window.clear();
				player.setPosition(Vector2f(1255.0f, 1970.0f));
				state = HOME;
			}

			//go up to the sky;
			if (player.getGlobalBounds().intersects(warperO[1].getGlobalBounds()))
			{
				window.clear();
				player.setPosition(Vector2f(1320.0f, 2280.0f));
				state = SKY;
			}

			//display window;
			window.display();
		}

		//stage 3;
		if (state == SKY)
		{
			//update entities;
			player.update(deltaTime);

			//map collision;
			for (int i = 0; i < blockS.size(); i++)	blockS[i].getCollider().checkCollider(playerCollision, 1.0f);

			//set view;
			view.setCenter(playerPosition);

			//clear screen;
			window.clear(Color(127, 231, 255));
			window.setView(view);

			//draw map texture;
			background3.draw(window);

			//draw entities;
			player.draw(window);

			//pause;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				//declare screen size;
				Vector2u ws = window.getSize();
				Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));

				//initialize button variables;
				button resume(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 150, "RESUME", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
				button txt(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 25, "PRESS ENTER TO CONTINUE", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

				//menu loop;
				while (window.isOpen())
				{
					Event evt;
					while (window.pollEvent(evt))
					{
						if (evt.type == Event::Closed) window.close();
					}

					view.setCenter(windowSize / 2.f);
					window.clear();
					window.setView(view);

					resume.draw(window);
					txt.draw(window);

					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						break;
					}

					window.display();
				}
			}

			//go down the beanstalk;
			if (player.getGlobalBounds().intersects(warperS[0].getGlobalBounds()))
			{
				window.clear();
				player.setPosition(Vector2f(1100.0f, 555.0f));
				state = OUTDOOR;
			}

			//go into the store;
			if (player.getGlobalBounds().intersects(warperS[1].getGlobalBounds()))
			{
				window.clear();
				state = STORE;
			}

			//go inside the castle;
			if (player.getGlobalBounds().intersects(warperS[2].getGlobalBounds()))
			{
				window.clear();
				player.setPosition(Vector2f(-700.f, 400.f));
				player.setAnimationRow(6);
				state = CASTLE;
			}

			//display window;
			window.display();
		}

		//store;
		if (state == STORE)
		{
			//set view;
			view.setCenter(windowSize / 2.f);

			//clear screen;
			window.clear();
			window.setView(view);

			//update entities;
			seller.updateStill(deltaTime);

			//update buttons
			welcomeText.update(mousePos);
			smallPotion.update(mousePos);
			mediumPotion.update(mousePos);
			greaterPotion.update(mousePos);
			manaPotion.update(mousePos);
			mehWand.update(mousePos);
			betterWand.update(mousePos);
			done.update(mousePos);
			thxText.update(mousePos);
			byeText.update(mousePos);
			returnToTheGame.update(mousePos);

			//draw entities;
			seller.draw(window);

			//draw platform;
			box1.draw(window);

			//draw buttons
			welcomeText.draw(window);
			smallPotion.draw(window);
			mediumPotion.draw(window);
			greaterPotion.draw(window);
			manaPotion.draw(window);
			mehWand.draw(window);
			betterWand.draw(window);
			done.draw(window);

			if (done.getGlobalBounds().contains(mousePos)) if (sf::Mouse::isButtonPressed(Mouse::Left)) buttonState = BYE;
			if (buttonState == BYE)
			{
				byeText.draw(window);
				returnToTheGame.draw(window);
			}

			//buying potions;
			if (smallPotion.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					buttonState = BOUGHT;
					//sHpPotion++;
					//coin -= 25;
				}
			}
			if (mediumPotion.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					buttonState = BOUGHT;
					//mHpPotion++;
					//coin -= 50;
				}
			}
			if (greaterPotion.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					buttonState = BOUGHT;
					//lHpPotion++;
					//coin -= 100;
				}
			}
			if (manaPotion.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					buttonState = BOUGHT;
					//mpPotion++;
					//coin -= 35;
				}
			}
			if (buttonState == BOUGHT)
			{
				thxText.draw(window);
			}

			//buying wands;
			if (mehWand.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					buttonState = BOUGHT;
					//wandState = KINDA;
					//coin -= 100;
				}
			}
			if (betterWand.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					buttonState = BOUGHT;
					//wandState = OP;
					//coin -= 100;
				}
			}

			//pause;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				//declare screen size;
				Vector2u ws = window.getSize();
				Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));

				//initialize button variables;
				button resume(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 150, "RESUME", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
				button txt(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 25, "PRESS ENTER TO CONTINUE", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

				//menu loop;
				while (window.isOpen())
				{
					Event evt;
					while (window.pollEvent(evt))
					{
						if (evt.type == Event::Closed) window.close();
					}

					view.setCenter(windowSize / 2.f);
					window.clear();
					window.setView(view);

					resume.draw(window);
					txt.draw(window);

					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						break;
					}

					window.display();
				}
			}

			//return to the game;
			if (returnToTheGame.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					player.setPosition(Vector2f(900.f, 1140.f));
					player.setAnimationRow(2);
					state = SKY;
				}
			}

			//display window;
			window.display();
		}

		//stage 4;
		if (state == CASTLE)
		{
			//update entities;
			player.updateBossFight(deltaTime);

			//initialize ground;
			Vector2f direction;
			for (int i = 0; i < platforms.size(); i++) platform& platform = platforms[i];
			for (platform& platform : platforms) if (platform.getCollider().checkGroundCollision(player.getCollider(), direction, 1.f)) player.onCollision(direction);

			//set view;
			view.setCenter(0.f, 0.f);

			//claer screen;
			window.clear();
			window.setView(view);

			//draw bsckground;
			castle.draw(window);

			//draw entities;
			player.draw(window);

			//pause;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				//declare screen size;
				Vector2u ws = window.getSize();
				Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));

				//initialize button variables;
				button resume(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 150, "RESUME", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
				button txt(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
					2.f, &font, 25, "PRESS ENTER TO CONTINUE", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

				//menu loop;
				while (window.isOpen())
				{
					Event evt;
					while (window.pollEvent(evt))
					{
						if (evt.type == Event::Closed) window.close();
					}

					view.setCenter(windowSize / 2.f);
					window.clear();
					window.setView(view);

					resume.draw(window);
					txt.draw(window);

					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						break;
					}

					window.display();
				}
			}

			//display window;
			window.display();
		}

		//game over;
		if (state == GAME_OVER)
		{
			//set view
			view.setCenter(windowSize / 2.f);

			//clear screen;
			window.clear();
			window.setView(view);

			//update buttons;
			gameOver.update(mousePos);
			scoreState.update(mousePos);
			returnToMenu.update(mousePos);

			//see score;
			if (scoreState.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					state = SCORE;
				}
			}

			//return to menu;
			if (returnToMenu.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					state = MENU;
				}
			}

			//draw buttons;
			gameOver.draw(window);
			scoreState.draw(window);
			returnToMenu.draw(window);

			//display window;
			window.display();
		}

		//view scores;
		if (state == SCORE)
		{
		}

		//end game credit;
		if (state == CREDIT)
		{
		}

		//draw bullets;
		if (wandState == REGULAR)
		{
			if (elapse[1].asSeconds() >= 0.2)
			{
				clock[1].restart();
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					bullet.body.setPosition(playerPosition);
					bullet.direction = player.direction;
					projectileArray.push_back(bullet);
					//playerMana -= 5;
				}
			}
			counter = 0;
			for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
			{
				projectileArray[counter].update(deltaTime);
				window.draw(projectileArray[counter].body);
				counter++;
			}
		}
		/*if (wandState == KINDA_GOOD)
		{
			if (elapse[1].asSeconds() >= 0.2)
			{
				clock[1].restart();
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					bullet.body.setPosition(playerPosition);
					bullet.direction = player.direction;
					projectileArray.push_back(bullet);
					//playerMana -= 5;
				}
			}
			counter = 0;
			for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
			{
				projectileArray[counter].update(deltaTime);
				window.draw(projectileArray[counter].body);
				counter++;
			}
		}
		if (wandState == OP)
		{
			if (elapse[1].asSeconds() >= 0.2)
			{
				clock[1].restart();
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					bullet.body.setPosition(playerPosition);
					bullet.direction = player.direction;
					projectileArray.push_back(bullet);
					//playerMana -= 5;
				}
			}
			counter = 0;
			for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
			{
				projectileArray[counter].update(deltaTime);
				window.draw(projectileArray[counter].body);
				counter++;
			}
		}*/
	}
	return 0;
}

//resizable view;
void resizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(viewheight * aspectRatio, viewheight);
}