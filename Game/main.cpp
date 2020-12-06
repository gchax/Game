#include "stdfn.h"
#include "player.h"
#include "platform.h"
#include "bitmap.h"
#include "enemy.h"
#include "button.h"
#include "textDisplay.h"
#include "item.h"


//resizable view;
void resizeView(const RenderWindow&, View&);


//main;
int main()
{
	//render window;
	RenderWindow window(VideoMode(viewWidght, viewHeight), "Jack!", Style::Close | Style::Resize);
	View view(Vector2f(0.0f, 0.0f), Vector2f(viewWidght, viewHeight));
	window.setFramerateLimit(framerateLimit);
	srand(time(NULL));


	//define screen size;
	Vector2u ws = window.getSize();
	Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));


	//initialize font;
	Font font;
	font.loadFromFile("8BitDragon.ttf");


	//initialize variables;
	int state = SKY;
	bool isHurt = false;
	bool isPause = false;
	bool isSpawned = false;
	bool isPlayerDead = false;
	bool isUnlocked = false;
	bool collisionCheat = false;
	bool gravityCheat = false;
	bool unlimitedManaCheat = false;
	bool unlimitedHealthCheat = false;
	int wandLevel = 0;
	int key = 0;
	int playerScore = 0;
	int playerMoney = 0;
	int hpPotion = 0;
	int mpPotion = 0;
	float maxhp = maxHP;
	float maxmp = maxMP;
	float playerHP = maxhp;
	float playerMP = maxmp;
	float playerGravity = gravity;


	//initialize player;
	Texture jack;
	jack.loadFromFile("jack.png");
	player player(&jack, Vector2u(8, 8), 0.07f, 600.0f);


	//declare delta time;
	float deltaTime = 0.0f;
	Clock clock[3];


	//initialzie map variables;
	Texture menubg;
	menubg.loadFromFile("jab.jpg");
	platform background(&menubg, Vector2f(windowSize), Vector2f(windowSize / 2.f));

	Texture jacklogo;
	jacklogo.loadFromFile("logo.png");
	platform logo(&jacklogo, Vector2f(621.f, 252.f), Vector2f(windowSize.x / 2.f, windowSize.y / 3.f));

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
	vector<bitmap> blockO0;
	vector<bitmap> blockO2;
	int outdoor[49][41] =
	{
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  1,  1,  2,  2,  2,  1,  1,  1,  1,  1,  1,  2,  2,  2,  1,  1,  1,  1,  1,  2,  2,  2,  1,  1},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
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
		{0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  0,  0,  0,  0,  0,  0,  0},
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
				blockO0.push_back(outdoor);
			}
			if (outdoor[mapY][mapX] == 2)
			{
				bitmap outdoor(nullptr, Vector2f(((mapX) * 120) + 60, ((mapY) * 120) + 60), Vector2f(120.f, 120.f));
				blockO2.push_back(outdoor);
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

	Texture mapCastle;
	mapCastle.loadFromFile("map_castle.png");
	platform castle(&mapCastle, Vector2f(5242.72f, 1080.0f), Vector2f(0.f, -50.f));
	vector<platform> platforms;
	platforms.push_back(platform(nullptr, Vector2f(5242.72f, 1.f), Vector2f(0.f, 400.f)));

	Texture storebg;
	storebg.loadFromFile("");
	//platform background(&storebg, Vector2f(), Vector2f(0.f, 0.f));

	Texture textbox;
	textbox.loadFromFile("textbox.png");
	platform box2(&textbox, Vector2f(1700.f, 380.f), Vector2f(windowSize.x / 2.f, 7.f * windowSize.y / 10.f));


	//initialize warpers;
	RectangleShape warperH;
	warperH.setPosition(Vector2f(1170.f, 2040.f));
	warperH.setSize(Vector2f(180.f, 10.f));

	RectangleShape pickUp;
	pickUp.setPosition(Vector2f(900.f, 1440.f));
	pickUp.setSize(Vector2f(90.f, 10.f));

	RectangleShape warperO[2];
	warperO[0].setPosition(Vector2f(3660.f, 4900.f));
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
	button startGame(Vector2f(windowSize.x / 2.f, 4.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 35, "START", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	startGame.setTextOutlineColor(Color::Black);
	startGame.setTextOutlineThickness(1);
	button score(Vector2f(windowSize.x / 2.f, 4.5f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 35, "LEADERBOARD", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	score.setTextOutlineColor(Color::Black);
	score.setTextOutlineThickness(1);
	button tutorial(Vector2f(windowSize.x / 2.f, 5.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 35, "TUTORIAL", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	tutorial.setTextOutlineColor(Color::Black);
	tutorial.setTextOutlineThickness(1);
	button credit(Vector2f(windowSize.x / 2.f, 5.5f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 35, "CREDITS", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	credit.setTextOutlineColor(Color::Black);
	credit.setTextOutlineThickness(1);
	button exitGame(Vector2f(windowSize.x / 2.f, 6.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 35, "EXIT", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	exitGame.setTextOutlineColor(Color::Black);
	exitGame.setTextOutlineThickness(1);

	string what_do_you_want[5] = { "How shall I serve thee, master?","What is it that you desire?","What is the purpose of thy presence?","Want some power-ups?","Ye shall only find good stuff here" };
	string bought[3] = { "Thank you, kind sir!\n    Anything else?", "Anything else?", "  Good choice!\nAnything else?" };
	int buttonState = UNSELECTED;
	button welcomeText(Vector2f(box2.body.getPosition().x, box2.body.getPosition().y + 15.f), Vector2f(windowSize.x, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
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
	button thxText(Vector2f(box2.body.getPosition().x, box2.body.getPosition().y + 15.f), Vector2f(4.f * windowSize.x / 5.f, 150.f), Color(186, 186, 186), Color(186, 186, 186), Color(186, 186, 186),
		2.f, &font, 55, bought[rand() % 3], Color::Black, Color::Black, Color::Black);
	button byeText(Vector2f(box2.body.getPosition().x, box2.body.getPosition().y + 15.f), Vector2f(4.f * windowSize.x / 5.f, 75.f), Color(186, 186, 186), Color(186, 186, 186), Color(186, 186, 186),
		2.f, &font, 45, "Gladly looking forward to seeing you again, kind sir.", Color::Black, Color::Black, Color::Black);
	button returnToTheGame(Vector2f(box2.body.getPosition().x + 555.f, box2.body.getPosition().y + 100.f), Vector2f(windowSize.x / 2.f, 50.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 20, "Return to the game.", Color::Black, Color(69, 69, 69, 255), Color(200, 200, 200, 255));

	button gameOver(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 150, "GAME OVER", Color::Red, Color::Red, Color::Red);
	button scoreState(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 25, "LEADERBOARD", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button returnToMenu(Vector2f(windowSize.x / 2.f, 9.f * windowSize.y / 10.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 25, "RETURN TO THE MENU", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

	button resume(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(500.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 150, "RESUME", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	button toMenu(Vector2f(windowSize.x / 2.f, 1.f * windowSize.y / 10.f), Vector2f(windowSize.x, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 25, "RESTART AND RETURN TO MENU", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));


	//initialize items;
	Texture awand;
	awand.loadFromFile("sparkle.png");
	item wand(&awand, Vector2u(1, 1), Vector2f(120.f, 120.f));
	wand.body.setPosition(Vector2f(945.0f, 1400.0f));

	Texture coins;
	coins.loadFromFile("coin.png");
	item coin(&coins, Vector2u(6, 1), Vector2f(60.f, 60.f));
	vector<item>::const_iterator coinIter;
	vector<item> coinArray;

	Texture fireball;
	fireball.loadFromFile("fireball.png");
	projectile bullet(&fireball, 1000.f, 100.f);
	vector<projectile>::const_iterator bulletIter;
	vector<projectile> projectileArray;

	Texture hp;
	hp.loadFromFile("hp.png");
	item hpp(&hp, Vector2u(1, 1), Vector2f(55.f, 72.5f));
	vector<item>::const_iterator hppIter;
	vector<item> hppArray;

	Texture mp;
	mp.loadFromFile("mp.png");
	item mpp(&mp, Vector2u(1, 1), Vector2f(40.f, 77.5f));
	vector<item>::const_iterator mppIter;
	vector<item> mppArray;
	
	Texture keys;
	keys.loadFromFile("key.png");
	item Key(&keys, Vector2u(1, 1), Vector2f(44.f, 21.5f));
	vector<item>::const_iterator keyIter;
	vector<item> keyArray;


	//initialize enemies;
	Texture gargoyle1;
	gargoyle1.loadFromFile("gargoyle1.png");
	enemy normalGargoyle1(&gargoyle1, Vector2u(5, 1), Vector2f(360.f, 232.f), Vector2f(1080.f, rand() % 500 + 6000), 0.08f, 20.f, 2000.f, 15);

	Texture gargoyle1_5;
	gargoyle1_5.loadFromFile("flippedgargoyle1.png");
	enemy normalGargoyle2(&gargoyle1_5, Vector2u(5, 1), Vector2f(360.f, 232.f), Vector2f(2520.f, 4500.f), 0.08f, 20.f, 2000.f, 15);

	Texture gargoyle2;
	gargoyle2.loadFromFile("gargoyle2.png");
	enemy toughGargoyle1(&gargoyle2, Vector2u(5, 2), Vector2f(360.f, 232.f), Vector2f(1080.f, rand() % 500 + 6000), 0.08f, 20.f, 2500.f, 25);

	Texture gargoyle2_5;
	gargoyle2_5.loadFromFile("flippedgargoyle2.png");
	enemy toughGargoyle2(&gargoyle2_5, Vector2u(5, 2), Vector2f(360.f, 232.f), Vector2f(2520.f, 4500.f), 0.08f, 20.f, 2500.f, 25);

	Texture titan1;
	titan1.loadFromFile("titan1.png");
	vector<enemy>::const_iterator titan1Iter;
	vector<enemy> titan1Array;
	enemy normalTitan1(&titan1, Vector2u(3, 4), Vector2f(228.f, 300.f), Vector2f(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f)), 0.5f, 200.f, 2000.f, 50);
	for (int i = 0;i < 10;i++)
	{
		titan1Array.push_back(normalTitan1);
		normalTitan1.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
	}

	Texture titan2;
	titan2.loadFromFile("titan2.png");
	vector<enemy>::const_iterator titan2Iter;
	vector<enemy> titan2Array;
	enemy normalTitan2(&titan1, Vector2u(3, 4), Vector2f(228.f, 300.f), Vector2f(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f)), 0.5f, 280.f, 5000.f, 100);
	for (int i = 0;i < 5;i++)
	{
		titan2Array.push_back(normalTitan2);
		normalTitan2.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
	}

	Texture monSeller;
	monSeller.loadFromFile("mon_seller.png");
	enemy seller(&monSeller, Vector2u(2, 1), Vector2f(33.f * 16, 49.f * 16), Vector2f(windowSize.x / 2.f + 432.f, windowSize.y / 2.f - 50.f), 0.8, 0.f, 0.f, 0);

	textDisplay moneyDp(Color::Yellow);
	moneyDp.text.setFont(font);
	vector<textDisplay>::const_iterator moneyIter;
	vector<textDisplay> moneyArray;

	textDisplay dmgDp(Color::Red);
	dmgDp.text.setFont(font);
	vector<textDisplay>::const_iterator dmgIter;
	vector<textDisplay> dmgArray;

	int entityValue = 0;
	int titan1Value = generateIntRandom(10, 50);


	//loop;
	while (window.isOpen())
	{
		//call delta time;
		deltaTime = clock[0].restart().asSeconds();
		if (deltaTime > 1.f / 20.f) deltaTime = 1.f / 20.f;

		//initialize time variables;
		Time elapse[3];
		elapse[0] = clock[0].getElapsedTime();
		elapse[1] = clock[1].getElapsedTime();
		elapse[2] = clock[2].getElapsedTime();

		//set window event;
		Event event;
		while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

		//check coordinate;
		Vector2i pos = Mouse::getPosition(window);
		Vector2f mousePos(static_cast<float>(pos.x), static_cast<float>(pos.y));

		//player variables;
		Vector2f playerPosition = player.body.getPosition();
		collider playerCollision = player.getCollider();
		player.hp = playerHP;
		if (playerHP >= maxHP) playerHP = maxHP;
		player.mp = playerMP;
		if (playerMP >= maxMP) playerMP = maxMP;
		player.money = playerMoney;
		if (playerMoney < 0) playerMoney = 0;
		if (wandLevel >= 60) wandLevel = 60;
		player.gravity = playerGravity;
		playerGUI gui(&font, player.hp, player.mp, player.money, playerScore, wandLevel);
		float atkSpd = 0.4f - wandLevel / 600.f;
		cout << "x = " << playerPosition.x << "\ty = " << playerPosition.y << endl;

		//counters;
		int titan1Counter = 0;
		int bulletCounter = 0;
		int coinCounter = 0;
		int hppCounter = 0;
		int mppCounter = 0;
		int keyCounter = 0;
		int moneyCounter = 0;
		int dmgCounter = 0;

		//textbox;
		string findKey;
		if (key != 5) findKey = ("FIND " + to_string(5 - key) + " MORE KEYS TO OPEN.");
		else findKey = "PRESS 'ENTER' TO ENTER.";
		platform box1(&textbox, Vector2f(680.f, 152.f), Vector2f(playerPosition.x + 10.f, playerPosition.y + 300.f));
		button pickItUp(Vector2f(box1.body.getPosition().x, box1.body.getPosition().y + 10.f), Vector2f(windowSize.x - 200.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "PRESS 'SPACE' TO PICK UP THE ITEM.", Color::Black, Color::Black, Color::Black);
		platform door(&textbox, Vector2f(680.f, 152.f), Vector2f(playerPosition.x + 10.f, playerPosition.y + 300.f));
		button unlock(Vector2f(box1.body.getPosition().x, box1.body.getPosition().y + 10.f), Vector2f(windowSize.x - 200.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, findKey, Color::Black, Color::Black, Color::Black);
		
		//menu;
		if (state == MENU)
		{
			//update buttons;
			startGame.update(mousePos);
			score.update(mousePos);
			tutorial.update(mousePos);
			credit.update(mousePos);
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
					player.body.setPosition(Vector2f(1125.0f, 595.0f));
					player.setAnimationRow(4);
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
			logo.draw(window);

			//draw buttons
			startGame.draw(window);
			score.draw(window);
			tutorial.draw(window);
			credit.draw(window);
			exitGame.draw(window);
		}

		//the game;
		if (!isPause && state == HOME || !isPause && state == OUTDOOR || !isPause && state == SKY || !isPause && state == CASTLE || !isPause && state == STORE)
		{
			//stage 1;
			if (state == HOME)
			{
				//update GUI;
				gui.updateStatus(deltaTime, windowSize, playerPosition);
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				player.update(deltaTime);

				//map collision;
				for (int i = 0; i < blockH.size(); i++) if (!collisionCheat) blockH[i].getCollider().checkCollider(playerCollision, 1.0f);

				//set view;
				view.setCenter(playerPosition);

				//clear window;
				window.clear(Color(16, 16, 16));
				window.setView(view);

				//draw map texture;
				background1.draw(window);

				//draw items;
				if (wandLevel == 0)
				{
					wand.draw(window);
					if (player.body.getGlobalBounds().intersects(pickUp.getGlobalBounds()))
					{
						box1.draw(window);
						pickItUp.update(mousePos);
						pickItUp.draw(window);
					}
				}

				//draw player;
				player.draw(window);

				//wand discovery;
				if (player.body.getGlobalBounds().intersects(pickUp.getGlobalBounds())) if (Keyboard::isKeyPressed(Keyboard::Space)) wandLevel = 1;

				//go outside;
				if (player.body.getGlobalBounds().intersects(warperH.getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(Vector2f(3720.0f, 5100.0f));
					state = OUTDOOR;
				}
			}

			//stage 2;
			if (state == OUTDOOR)
			{
				//update GUI;
				gui.updateStatus(deltaTime, windowSize, playerPosition);
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				player.update(deltaTime);
				/*if (player.getPosition().y >= 5000 && player.getPosition().y <= 6500) normalGargoyle1.updateFly(deltaTime, player.getPosition());
				else normalGargoyle1.updateStill(deltaTime);
				normalGargoyle2.updateStill(deltaTime);*/

				//map collision;
				if (!collisionCheat)
				{
					for (int i = 0; i < blockO0.size(); i++) blockO0[i].getCollider().checkCollider(playerCollision, 1.0f);
					for (int i = 0; i < blockO2.size(); i++) blockO2[i].getCollider().checkCollider(playerCollision, 1.0f);
				}

				//set view;
				view.setCenter(playerPosition);

				//clear screen;
				window.clear(Color(127, 231, 255));
				window.setView(view);

				//draw map texture;
				background2.draw(window);

				//draw entities;
				/*normalGargoyle1.draw(window);
				normalGargoyle2.draw(window);*/
				player.draw(window);

				//go back inside the house;
				if (player.body.getGlobalBounds().intersects(warperO[0].getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(Vector2f(1255.0f, 1970.0f));
					state = HOME;
				}

				//go up to the sky;
				if (player.body.getGlobalBounds().intersects(warperO[1].getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(Vector2f(1320.0f, 2280.0f));
					state = SKY;
				}
			}

			//stage 3;
			if (state == SKY)
			{
				//update GUI;
				gui.updateStatus(deltaTime, windowSize, playerPosition);
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				player.update(deltaTime);

				//map collision;
				for (int i = 0; i < blockS.size(); i++) if (!collisionCheat) blockS[i].getCollider().checkCollider(playerCollision, 1.0f);

				//set view;
				view.setCenter(playerPosition);

				//clear screen;
				window.clear(Color(127, 231, 255));
				window.setView(view);
				
				//draw map texture;
				background3.draw(window);

				//draw items;
				coinCounter = 0;
				for (coinIter = coinArray.begin();coinIter != coinArray.end();coinIter++)
				{
					coinArray[coinCounter].update(deltaTime);
					window.draw(coinArray[coinCounter].body);
					coinCounter++;
				}
				hppCounter = 0;
				for (hppIter = hppArray.begin();hppIter != hppArray.end();hppIter++)
				{
					hppArray[hppCounter].update(deltaTime);
					window.draw(hppArray[hppCounter].body);
					hppCounter++;
				}
				mppCounter = 0;
				for (mppIter = mppArray.begin();mppIter != mppArray.end();mppIter++)
				{
					mppArray[mppCounter].update(deltaTime);
					window.draw(mppArray[mppCounter].body);
					mppCounter++;
				}
				keyCounter = 0;
				for (keyIter = keyArray.begin();keyIter != keyArray.end();keyIter++)
				{
					keyArray[keyCounter].update(deltaTime);
					window.draw(keyArray[keyCounter].body);
					keyCounter++;
				}

				//draw entities;
				if (normalTitan1.isRespawnwed) //respawn;
				{
					normalTitan1.isRespawnwed = false;
					titan1Array.push_back(normalTitan1);
					normalTitan1.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
				}
				titan1Counter = 0; //hit;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					collider titan1Collision = titan1Array[titan1Counter].getCollider();
					for (int i = 0; i < blockS.size(); i++) blockS[i].getCollider().checkCollider(titan1Collision, 1.0f);

					if (player.body.getGlobalBounds().intersects(titan1Array[titan1Counter].body.getGlobalBounds()))
					{
						player.hurt();
						if (elapse[1].asSeconds() >= 0.5f)
						{
							clock[1].restart();
							int damage = titan1Array[titan1Counter].damage;
							dmgDp.text.setString("-" + to_string(damage));
							dmgDp.text.setPosition(playerPosition);
							dmgArray.push_back(dmgDp);
							if (!unlimitedHealthCheat) playerHP -= damage;
						}
					}
					titan1Counter++;
				}
				titan1Counter = 0; //die;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					if (titan1Array[titan1Counter].isDead)
					{
						coin.body.setPosition(titan1Array[titan1Counter].body.getPosition());
						coinArray.push_back(coin);
						if (chance(14) == 0)
						{
							hpp.body.setPosition(titan1Array[titan1Counter].body.getPosition().x + 25.f, titan1Array[titan1Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(9) == 0)
						{
							mpp.body.setPosition(titan1Array[titan1Counter].body.getPosition().x - 25.f, titan1Array[titan1Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(64) == 0)
						{
							Key.body.setPosition(titan1Array[titan1Counter].body.getPosition().x, titan1Array[titan1Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						entityValue = titan1Value;
						titan1Array.erase(titan1Iter);
						normalTitan1.isRespawnwed = true;
						break;
					}
					titan1Counter++;
				}
				titan1Counter = 0; //draw titan1;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					titan1Array[titan1Counter].updateWalk(deltaTime);
					window.draw(titan1Array[titan1Counter].body);
					titan1Counter++;
				}
				player.draw(window); //draw player;

				//go down the beanstalk;
				if (player.body.getGlobalBounds().intersects(warperS[0].getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(Vector2f(1100.0f, 555.0f));
					state = OUTDOOR;
				}

				//go into the store;
				if (player.body.getGlobalBounds().intersects(warperS[1].getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(windowSize / 2.f);
					buttonState = IDLE;
					state = STORE;
				}

				//go inside the castle;
				if (Keyboard::isKeyPressed(Keyboard::Return) && key == 5) isUnlocked = true;
				if (player.body.getGlobalBounds().intersects(warperS[2].getGlobalBounds()))
				{
					if (isUnlocked)
					{
						window.clear();
						player.body.setPosition(Vector2f(-700.f, 350.f));
						player.setAnimationRow(6);
						state = CASTLE;
					}
					if (!isUnlocked)
					{
						door.draw(window);
						unlock.update(mousePos);
						unlock.draw(window);
					}
				}
			}

			//stage 4;
			if (state == CASTLE)
			{
				//update GUI;
				gui.updateCastle(deltaTime, windowSize);

				//update entities;
				if (!gravityCheat) player.updateBossFight(deltaTime);
				else player.update(deltaTime);

				//initialize ground;
				Vector2f direction;
				for (int i = 0; i < platforms.size(); i++) platform& platform = platforms[i];
				for (platform& platform : platforms) if (!gravityCheat) if (platform.getCollider().checkGroundCollision(player.getCollider(), direction, 1.f)) player.onCollision(direction);

				//set view;
				view.setCenter(0.f, 0.f);

				//claer screen;
				window.clear();
				window.setView(view);

				//draw background;
				castle.draw(window);

				//draw entities;
				player.draw(window);
			}

			//store;
			if (state == STORE)
			{
				//update GUI;
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				seller.updateStill(deltaTime);

				//set view;
				view.setCenter(windowSize / 2.f);

				//clear screen;
				window.clear();
				window.setView(view);

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
				box2.draw(window);

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

				//draw GUI;
				gui.drawCoin(window);
				gui.drawWandState(window);

				//buying potions;
				if (smallPotion.getGlobalBounds().contains(mousePos))
				{
					if (sf::Mouse::isButtonPressed(Mouse::Left))
					{
						buttonState = BOUGHT;
						//hpPotion++;
						playerMoney -= 25;
					}
				}
				if (mediumPotion.getGlobalBounds().contains(mousePos))
				{
					if (sf::Mouse::isButtonPressed(Mouse::Left))
					{
						buttonState = BOUGHT;
						//hpPotion++;
						playerMoney -= 50;
					}
				}
				if (greaterPotion.getGlobalBounds().contains(mousePos))
				{
					if (sf::Mouse::isButtonPressed(Mouse::Left))
					{
						buttonState = BOUGHT;
						//hpPotion++;
						playerMoney -= 100;
					}
				}
				if (manaPotion.getGlobalBounds().contains(mousePos))
				{
					if (sf::Mouse::isButtonPressed(Mouse::Left))
					{
						buttonState = BOUGHT;
						//mpPotion++;
						playerMoney -= 35;
					}
				}

				//buying wands;
				if (mehWand.getGlobalBounds().contains(mousePos))
				{
					if (sf::Mouse::isButtonPressed(Mouse::Left))
					{
						buttonState = BOUGHT;
						wandLevel++;
						playerMoney -= 500;
					}
				}

				if (buttonState == BOUGHT)
				{
					thxText.draw(window);
				}

				//return to the game;
				if (returnToTheGame.getGlobalBounds().contains(mousePos))
				{
					if (sf::Mouse::isButtonPressed(Mouse::Left))
					{
						window.clear();
						player.body.setPosition(Vector2f(900.f, 1140.f));
						player.setAnimationRow(2);
						player.direction = DOWN;
						state = SKY;
					}
				}
			}

			//events;
			if (state == HOME || state == OUTDOOR || state == SKY || state == CASTLE)
			{
				//update player's stats
				playerHP += 0.1f * deltaTime;
				playerMP += 1.f * deltaTime;
				if (player.hp <= 0) isPlayerDead = true;
				
				//bullet events;
				if (wandLevel != 0)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space) && playerMP > 0) //release bullet;
					{
						if (elapse[2].asSeconds() >= atkSpd)
						{
							clock[2].restart();
							bullet.body.setPosition(playerPosition);
							bullet.direction = player.direction;
							projectileArray.push_back(bullet);
							if (!unlimitedManaCheat) playerMP -= 3.f;
						}
					}
					bulletCounter = 0; //hit enemies;
					for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
					{
						if (state == HOME && !collisionCheat) for (int i = 0; i < blockH.size(); i++) if (blockH[i].getGlobalBounds().intersects(projectileArray[bulletCounter].body.getGlobalBounds())) projectileArray[bulletCounter].isCollided = true;
						if (state == OUTDOOR)
						{

						}
						if (state == SKY)
						{
							titan1Counter = 0; //titan1 got hit;
							for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(titan1Array[titan1Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									titan1Array[titan1Counter].body.setFillColor(Color::Red);
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 5.f);
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(titan1Array[titan1Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									titan1Array[titan1Counter].hp -= damage;
									if (titan1Array[titan1Counter].hp <= 0.f)
									{
										titan1Array[titan1Counter].isDead = true;
										playerScore += 500;
									}
								}
								titan1Counter++;
							}
						}
						if (state == CASTLE && !collisionCheat)
						{

						}
						if (projectileArray[bulletCounter].isCollided) //delete bullets;
						{
							projectileArray.erase(bulletIter);
							break;
						}
						bulletCounter++;
					}
					bulletCounter = 0; //draw bullets;
					for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
					{
						projectileArray[bulletCounter].update(deltaTime);
						window.draw(projectileArray[bulletCounter].body);
						bulletCounter++;
					}
				}

				//items pick up;
				coinCounter = 0; //coins pick up;
				for (coinIter = coinArray.begin(); coinIter != coinArray.end();coinIter++)
				{
					if (player.body.getGlobalBounds().intersects(coinArray[coinCounter].body.getGlobalBounds())) coinArray[coinCounter].isPickedUp = true;
					if (coinArray[coinCounter].isPickedUp)
					{
						playerMoney += entityValue;
						moneyDp.text.setString("+$" + to_string(entityValue));
						moneyDp.text.setPosition(coinArray[coinCounter].body.getPosition());
						moneyArray.push_back(moneyDp);
						coinArray.erase(coinIter);
						break;
					}
					coinCounter++;
				}
				hppCounter = 0; //hp potions pick up;
				for (hppIter = hppArray.begin(); hppIter != hppArray.end();hppIter++)
				{
					if (player.body.getGlobalBounds().intersects(hppArray[hppCounter].body.getGlobalBounds())) hppArray[hppCounter].isPickedUp = true;
					if (hppArray[hppCounter].isPickedUp)
					{
						hpPotion++;
						hppArray.erase(hppIter);
						break;
					}
					hppCounter++;
				}
				mppCounter = 0; //mp potions pick up;
				for (mppIter = mppArray.begin(); mppIter != mppArray.end();mppIter++)
				{
					if (player.body.getGlobalBounds().intersects(mppArray[mppCounter].body.getGlobalBounds())) mppArray[mppCounter].isPickedUp = true;
					if (mppArray[mppCounter].isPickedUp)
					{
						mpPotion++;
						mppArray.erase(mppIter);
						break;
					}
					mppCounter++;
				}
				keyCounter = 0; //keys pick up;
				for (keyIter = keyArray.begin(); keyIter != keyArray.end();keyIter++)
				{
					if (player.body.getGlobalBounds().intersects(keyArray[keyCounter].body.getGlobalBounds())) keyArray[keyCounter].isPickedUp = true;
					if (keyArray[keyCounter].isPickedUp)
					{
						key++;
						keyArray.erase(keyIter);
						break;
					}
					keyCounter++;
				}

				//display stats update;
				moneyCounter = 0;
				for (moneyIter = moneyArray.begin();moneyIter != moneyArray.end();moneyIter++)
				{
					moneyArray[moneyCounter].update(deltaTime);
					window.draw(moneyArray[moneyCounter].text);
					if (moneyArray[moneyCounter].destroy)
					{
						moneyArray.erase(moneyIter);
						break;
					}
					moneyCounter++;
				}
				dmgCounter = 0;
				for (dmgIter = dmgArray.begin();dmgIter != dmgArray.end();dmgIter++)
				{
					dmgArray[dmgCounter].update(deltaTime);
					window.draw(dmgArray[dmgCounter].text);
					if (dmgArray[dmgCounter].destroy)
					{
						dmgArray.erase(dmgIter);
						break;
					}
					dmgCounter++;
				}

				//draw GUI;
				gui.drawStatus(window);
				gui.drawCoin(window);
				gui.drawWandState(window);

				//buffs;


				//cheats;
				if (Keyboard::isKeyPressed(Keyboard::Num1) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					collisionCheat = true;
					cout << "collision cheat activated!" << endl;

				}
				if (Keyboard::isKeyPressed(Keyboard::Num1) && Keyboard::isKeyPressed(Keyboard::End))
				{
					collisionCheat = false;
					cout << "collision cheat deactivated!" << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Num2) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					gravityCheat = true;
					cout << "flying cheat activated!" << endl;

				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) && Keyboard::isKeyPressed(Keyboard::End))
				{
					gravityCheat = false;
					cout << "flying cheat cheat deactivated!" << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Num3) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					unlimitedHealthCheat = true;
					cout << "invincible mode activated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num3) && Keyboard::isKeyPressed(Keyboard::End))
				{
					unlimitedHealthCheat = false;
					cout << "invincible mode deactivated!" << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Num4) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					unlimitedManaCheat = true;
					cout << "gatling mode activated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num4) && Keyboard::isKeyPressed(Keyboard::End))
				{
					unlimitedManaCheat = false;
					cout << "gatling mode deactivated!" << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::K)) key = 5;
				if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::K)) key = 0;

				if (Keyboard::isKeyPressed(Keyboard::R) && Keyboard::isKeyPressed(Keyboard::I) && Keyboard::isKeyPressed(Keyboard::P))
				{
					cout << "ur dead" << endl;
					isPlayerDead = true;
				}

				if (isPlayerDead)
				{
					window.clear();
					state = GAME_OVER;
				}
			}

			//pause;
			if (Keyboard::isKeyPressed(Keyboard::Escape)) isPause = true;
		}

		//pause menu;
		if (isPause)
		{
			//update buttons;
			resume.update(mousePos);
			toMenu.update(mousePos);

			//set view;
			view.setCenter(windowSize / 2.f);
			window.clear();
			window.setView(view);

			//draw buttons;
			resume.draw(window);
			toMenu.draw(window);

			if (resume.getGlobalBounds().contains(mousePos)) if (sf::Mouse::isButtonPressed(Mouse::Left)) isPause = false;

			//restart;
			if (toMenu.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					state = MENU;
					wandLevel = 0;
					isPause = false;
					playerScore = 0;
					playerMoney = 0;
					playerHP = maxHP;
					playerMP = maxMP;
				}
			}
		}

		//game over;
		if (state == GAME_OVER)
		{
			//restart game;
			isPlayerDead = false;

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
					wandLevel = 0;
					playerScore = 0;
					playerMoney = 0;
					playerHP = maxHP;
					playerMP = maxMP;
				}
			}

			//draw buttons;
			gameOver.draw(window);
			scoreState.draw(window);
			returnToMenu.draw(window);
		}

		//view scores;
		if (state == SCORE)
		{
			window.clear();
		}

		//tutorial;
		if (state == TUTORIAL)
		{
			window.clear();
		}

		//end game credit;
		if (state == CREDIT)
		{
			window.clear();
		}

		//display window;
		window.display();
	}
	return 0;
}

//resizable view;
void resizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(viewHeight * aspectRatio, viewHeight);
}