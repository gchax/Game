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
	RenderWindow window(VideoMode(viewWidght, viewHeight), "Jack!", Style::Close | Style::Fullscreen);
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
	int state = CASTLE;
	bool isHurt = false;
	bool isPause = false;
	bool isSpawned = false;
	bool isPlayerDead = false;
	bool isUnlocked = false;
	bool collisionCheat = false;
	bool gravityCheat = false;
	bool unlimitedManaCheat = false;
	bool unlimitedHealthCheat = false;
	bool useHpPotion = false;
	bool useMpPotion = false;
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

	//initialize textures;
	Texture HPP;
	HPP.loadFromFile("hpp.jpg");

	Texture MPP;
	MPP.loadFromFile("mpp.jpg");

	Texture jack;
	jack.loadFromFile("jack.png");

	Texture menubg;
	menubg.loadFromFile("jab.jpg");

	Texture jacklogo;
	jacklogo.loadFromFile("logo.png");

	Texture homebg;
	homebg.loadFromFile("map_home.png");

	Texture outdoorbg;
	outdoorbg.loadFromFile("map_outdoor.png");

	Texture skybg;
	skybg.loadFromFile("map_sky.png");

	Texture mapCastle;
	mapCastle.loadFromFile("map_castle.png");

	Texture storebg;
	storebg.loadFromFile("shopbg.jpg");

	Texture textbox;
	textbox.loadFromFile("textbox.png");

	Texture awand;
	awand.loadFromFile("sparkle.png");

	Texture coins;
	coins.loadFromFile("coin.png");

	Texture fireball;
	fireball.loadFromFile("fireball.png");

	Texture hp;
	hp.loadFromFile("hp.png");

	Texture mp;
	mp.loadFromFile("mp.png");

	Texture keys;
	keys.loadFromFile("key.png");

	Texture gargoyle1;
	gargoyle1.loadFromFile("gargoyle1.png");

	Texture gargoyle1Ball;
	gargoyle1Ball.loadFromFile("ballg1.png");

	Texture gargoyle2;
	gargoyle2.loadFromFile("gargoyle2.png");

	Texture gargoyle2Ball;
	gargoyle2Ball.loadFromFile("ballg2.png");

	Texture titan1;
	titan1.loadFromFile("titan1.png");

	Texture titan2;
	titan2.loadFromFile("titan2.png");

	Texture titan2Ball;
	titan2Ball.loadFromFile("ballt2.png");

	Texture monSeller;
	monSeller.loadFromFile("mon_seller.png");

	Texture theboss;
	theboss.loadFromFile("boss.png");


	//initialize player;
	player player(&jack, Vector2u(8, 8), 0.07f, 600.0f);


	//declare delta time;
	float deltaTime = 0.0f;
	Clock clock[10];


	//initialzie map variables;
	platform background(&menubg, Vector2f(windowSize), Vector2f(windowSize / 2.f));

	platform logo(&jacklogo, Vector2f(621.f, 252.f), Vector2f(windowSize.x / 2.f, windowSize.y / 3.f));

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

	platform castle(&mapCastle, Vector2f(5242.72f, 1080.0f), Vector2f(0.f, -50.f));
	vector<platform> platforms;
	platforms.push_back(platform(nullptr, Vector2f(5242.72f, 1.f), Vector2f(0.f, 400.f)));

	platform store(&storebg, Vector2f(1920.f, 1080.f), Vector2f(960.f, 540.f));
	store.body.setFillColor(Color(150, 150, 150, 150));

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
		2.f, &font, 45, "START", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	startGame.setTextOutlineColor(Color::Black);
	startGame.setTextOutlineThickness(2);
	button score(Vector2f(windowSize.x / 2.f, 4.5f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 45, "LEADERBOARD", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	score.setTextOutlineColor(Color::Black);
	score.setTextOutlineThickness(2);
	button tutorial(Vector2f(windowSize.x / 2.f, 5.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 45, "TUTORIAL", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	tutorial.setTextOutlineColor(Color::Black);
	tutorial.setTextOutlineThickness(2);
	button credit(Vector2f(windowSize.x / 2.f, 5.5f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 45, "CREDITS", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	credit.setTextOutlineColor(Color::Black);
	credit.setTextOutlineThickness(2);
	button exitGame(Vector2f(windowSize.x / 2.f, 6.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
		2.f, &font, 45, "EXIT", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
	exitGame.setTextOutlineColor(Color::Black);
	exitGame.setTextOutlineThickness(2);

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
	item wand(&awand, Vector2u(1, 1), Vector2f(120.f, 120.f));
	wand.body.setPosition(Vector2f(945.0f, 1400.0f));

	item coin(&coins, Vector2u(6, 1), Vector2f(60.f, 60.f));
	vector<item>::const_iterator coinIter;
	vector<item> coinArray;

	projectile bullet(&fireball, 1000.f, 100.f);
	vector<projectile>::const_iterator bulletIter;
	vector<projectile> projectileArray;

	item hpp(&hp, Vector2u(1, 1), Vector2f(55.f, 72.5f));
	vector<item>::const_iterator hppIter;
	vector<item> hppArray;

	item mpp(&mp, Vector2u(1, 1), Vector2f(40.f, 77.5f));
	vector<item>::const_iterator mppIter;
	vector<item> mppArray;

	item Key(&keys, Vector2u(1, 1), Vector2f(44.f, 21.5f));
	vector<item>::const_iterator keyIter;
	vector<item> keyArray;


	//initialize enemies;
	enemy normalGargoyle(&gargoyle1, Vector2u(5, 2), Vector2f(360.f, 232.f), Vector2f(generateIntRandom(500, 100), generateIntRandom(2300, 700)), 0.1f, 180.f, 500.f, 15);
	vector<enemy>::const_iterator gargoyle1Iter;
	vector<enemy> gargoyle1Array;
	for (int i = 0;i < 7;i++)
	{
		gargoyle1Array.push_back(normalGargoyle);
		normalGargoyle.body.setPosition(generateIntRandom(500, 100), generateIntRandom(2300, 700));
	}
	for (int i = 0;i < 8;i++)
	{
		gargoyle1Array.push_back(normalGargoyle);
		normalGargoyle.body.setPosition(generateIntRandom(500, 1500), generateIntRandom(2300, 700));
	}
	projectile gargoyle1Bullet(&gargoyle1Ball, 1000.f, 30.f);
	vector<projectile>::const_iterator gargoyle1BulletIter;
	vector<projectile> gargoyle1BulletArray;

	enemy advancedGargoyle(&gargoyle2, Vector2u(5, 2), Vector2f(348.f, 372.f), Vector2f(generateIntRandom(500, 100), generateIntRandom(2300, 700)), 0.1f, 250.f, 1500.f, 25);
	vector<enemy>::const_iterator gargoyle2Iter;
	vector<enemy> gargoyle2Array;
	for (int i = 0;i < 2;i++)
	{
		gargoyle2Array.push_back(advancedGargoyle);
		advancedGargoyle.body.setPosition(generateIntRandom(500, 0), generateIntRandom(2300, 700));
	}
	for (int i = 0;i < 3;i++)
	{
		gargoyle2Array.push_back(advancedGargoyle);
		advancedGargoyle.body.setPosition(generateIntRandom(500, 1600), generateIntRandom(2300, 700));
	}
	projectile gargoyle2Bullet(&gargoyle2Ball, 1000.f, 30.f);
	vector<projectile>::const_iterator gargoyle2BulletIter;
	vector<projectile> gargoyle2BulletArray;

	enemy normalTitan(&titan1, Vector2u(3, 4), Vector2f(304.f, 400.f), Vector2f(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f)), 0.5f, 250.f, 2500.f, 30);
	vector<enemy>::const_iterator titan1Iter;
	vector<enemy> titan1Array;
	for (int i = 0;i < 10;i++)
	{
		titan1Array.push_back(normalTitan);
		normalTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
	}
	enemy advancedTitan(&titan2, Vector2u(3, 4), Vector2f(304.f, 400.f), Vector2f(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f)), 0.5f, 280.f, 5000.f, 70);
	vector<enemy>::const_iterator titan2Iter;
	vector<enemy> titan2Array;
	for (int i = 0;i < 5;i++)
	{
		titan2Array.push_back(advancedTitan);
		advancedTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
	}
	projectile titan2Bullet(&titan2Ball, 1000.f, 30.f);
	vector<projectile>::const_iterator titan2BulletIter;
	vector<projectile> titan2BulletArray;

	enemy seller(&monSeller, Vector2u(2, 1), Vector2f(33.f * 16, 49.f * 16), Vector2f(windowSize.x / 2.f + 432.f, windowSize.y / 2.f - 50.f), 0.8, 0.f, 0.f, 0);

	enemy boss(&theboss, Vector2u(2, 3), Vector2f(850.f, 800.f), Vector2f(0.f, 0.f), 1.f, 1, 1000000, 300);

	int entityValue = 0;

	textDisplay moneyDp(Color::Yellow);
	moneyDp.text.setFont(font);
	vector<textDisplay>::const_iterator moneyIter;
	vector<textDisplay> moneyArray;

	textDisplay hppDp(Color(255, 155, 0));
	hppDp.text.setFont(font);
	vector<textDisplay>::const_iterator hppPickUpIter;
	vector<textDisplay> hppPickUpArray;

	textDisplay mppDp(Color::Magenta);
	mppDp.text.setFont(font);
	vector<textDisplay>::const_iterator mppPickUpIter;
	vector<textDisplay> mppPickUpArray;

	textDisplay keyDp(Color(255, 239, 84));
	keyDp.text.setFont(font);
	vector<textDisplay>::const_iterator keyPickUpIter;
	vector<textDisplay> keyPickUpArray;

	textDisplay dmgDp(Color::Red);
	dmgDp.text.setFont(font);
	vector<textDisplay>::const_iterator dmgIter;
	vector<textDisplay> dmgArray;


	//loop;
	while (window.isOpen())
	{
		//call delta time;
		deltaTime = clock[0].restart().asSeconds();
		if (deltaTime > 1.f / 20.f) deltaTime = 1.f / 20.f;

		//initialize time variables;
		Time elapse[10];
		elapse[0] = clock[0].getElapsedTime();
		elapse[1] = clock[1].getElapsedTime();
		elapse[2] = clock[2].getElapsedTime();
		elapse[3] = clock[3].getElapsedTime();
		elapse[4] = clock[4].getElapsedTime();
		elapse[5] = clock[5].getElapsedTime();
		elapse[6] = clock[6].getElapsedTime();
		elapse[7] = clock[7].getElapsedTime();
		elapse[8] = clock[8].getElapsedTime();
		elapse[9] = clock[9].getElapsedTime();

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
		playerGUI gui(&font, &HPP, &MPP, player.hp, maxhp, player.mp, maxmp, hpPotion, mpPotion, player.money, playerScore, wandLevel, key);
		float atkSpd = 0.4f - wandLevel / 600.f;
		cout << "x = " << playerPosition.x << "\ty = " << playerPosition.y << endl;

		//loop counters;
		int gargoyle1Counter = 0;
		int gargoyle1BulletCounter = 0;
		int gargoyle2Counter = 0;
		int gargoyle2BulletCounter = 0;
		int titan1Counter = 0;
		int titan2Counter = 0;
		int titan2BulletCounter = 0;
		int bulletCounter = 0;
		int coinCounter = 0;
		int hppCounter = 0;
		int mppCounter = 0;
		int keyCounter = 0;
		int moneyCounter = 0;
		int hppPickUpCounter = 0;
		int mppPickUpCounter = 0;
		int keyPickUpCounter = 0;
		int dmgCounter = 0;

		//entities' value;
		int gargoyle1Value = generateIntRandom(10, 20);
		int gargoyle2Value = generateIntRandom(10, 50);
		int titan1Value = generateIntRandom(10, 80);
		int titan2Value = generateIntRandom(10, 150);

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

		//menu//
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

			//tutorial;
			if (tutorial.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					state = TUTORIAL;
				}
			}

			//credits;
			if (credit.getGlobalBounds().contains(mousePos))
			{
				if (sf::Mouse::isButtonPressed(Mouse::Left))
				{
					window.clear();
					state = CREDIT;
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
			//stage 1//
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

			//stage 2//
			if (state == OUTDOOR)
			{
				//update GUI;
				gui.updateStatus(deltaTime, windowSize, playerPosition);
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				player.update(deltaTime);

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

				//draw items;
				coinCounter = 0;
				for (coinIter = coinArray.begin();coinIter != coinArray.end();coinIter++)
				{
					coinArray[coinCounter].update(deltaTime);
					window.draw(coinArray[coinCounter].body);
					coinArray[coinCounter].lifetime++;
					if (coinArray[coinCounter].lifetime >= 500)
					{
						coinArray[coinCounter].lifetime = 0;
						coinArray[coinCounter].destroy = true;
					}
					coinCounter++;
				}
				hppCounter = 0;
				for (hppIter = hppArray.begin();hppIter != hppArray.end();hppIter++)
				{
					hppArray[hppCounter].update(deltaTime);
					window.draw(hppArray[hppCounter].body);
					hppArray[hppCounter].lifetime++;
					if (hppArray[hppCounter].lifetime >= 500)
					{
						hppArray[hppCounter].lifetime = 0;
						hppArray[hppCounter].destroy = true;
					}
					hppCounter++;
				}
				mppCounter = 0;
				for (mppIter = mppArray.begin();mppIter != mppArray.end();mppIter++)
				{
					mppArray[mppCounter].update(deltaTime);
					window.draw(mppArray[mppCounter].body);
					mppArray[mppCounter].lifetime++;
					if (mppArray[mppCounter].lifetime >= 500)
					{
						mppArray[mppCounter].lifetime = 0;
						mppArray[mppCounter].destroy = true;
					}
					mppCounter++;
				}
				keyCounter = 0;
				for (keyIter = keyArray.begin();keyIter != keyArray.end();keyIter++)
				{
					keyArray[keyCounter].update(deltaTime);
					window.draw(keyArray[keyCounter].body);
					keyArray[keyCounter].lifetime++;
					if (keyArray[keyCounter].lifetime >= 1800)
					{
						keyArray[keyCounter].lifetime = 0;
						keyArray[keyCounter].destroy = true;
					}
					keyCounter++;
				}

				//draw entities;
				if (normalGargoyle.isRespawned) //respawn gargoyle1;
				{
					int LoR = generateIntRandom(2, 1);
					normalGargoyle.isRespawned = false;
					if (LoR == 1) normalGargoyle.body.setPosition(generateIntRandom(500, 100), generateIntRandom(2300, 700));
					else if (LoR == 2) normalGargoyle.body.setPosition(generateIntRandom(500, 1500), generateIntRandom(2300, 700));
					gargoyle1Array.push_back(normalGargoyle);
				}
				gargoyle1Counter = 0; //gargoyle1 aggroed;
				for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
				{
					if (gargoyle1Array[gargoyle1Counter].isAggroed)
					{
						gargoyle1Array[gargoyle1Counter].action = generateIntRandom(2, 1);
						if (elapse[3].asMilliseconds() >= 10.f)
						{
							clock[3].restart();
							gargoyle1Array[gargoyle1Counter].updateAggroedFly(deltaTime, playerPosition);
						}
					}
					if (gargoyle1Array[gargoyle1Counter].action >= 2)
					{
						if (elapse[4].asSeconds() >= 1.f)
						{
							clock[4].restart();
							if (playerPosition.x < gargoyle1Array[gargoyle1Counter].body.getPosition().x && abs(playerPosition.y - gargoyle1Array[gargoyle1Counter].body.getPosition().y) <= 40)
							{
								gargoyle1Bullet.direction = LEFT;
								gargoyle1Bullet.body.setPosition(gargoyle1Array[gargoyle1Counter].body.getPosition());
								gargoyle1BulletArray.push_back(gargoyle1Bullet);
								gargoyle1Array[gargoyle1Counter].direction = LEFT;
							}
							if (playerPosition.x > gargoyle1Array[gargoyle1Counter].body.getPosition().x && abs(playerPosition.y - gargoyle1Array[gargoyle1Counter].body.getPosition().y) <= 40)
							{
								gargoyle1Bullet.direction = RIGHT;
								gargoyle1Bullet.body.setPosition(gargoyle1Array[gargoyle1Counter].body.getPosition());
								gargoyle1BulletArray.push_back(gargoyle1Bullet);
								gargoyle1Array[gargoyle1Counter].direction = RIGHT;
							}
						}
					}
					gargoyle1Counter++;
				}
				gargoyle1Counter = 0; //gargoyle1 die;
				for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
				{
					if (gargoyle1Array[gargoyle1Counter].isDead)
					{
						coin.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y);
						coinArray.push_back(coin);
						if (chance(24) == 0)
						{
							hpp.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(19) == 0)
						{
							mpp.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(299) == 0)
						{
							Key.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						entityValue = gargoyle1Value;
						gargoyle1Array.erase(gargoyle1Iter);
						normalGargoyle.isRespawned = true;
						break;
					}
					gargoyle1Counter++;
				}
				gargoyle1Counter = 0; //draw gargoyle1;
				for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
				{
					gargoyle1Array[gargoyle1Counter].updateFly(deltaTime);
					window.draw(gargoyle1Array[gargoyle1Counter].body);
					gargoyle1Counter++;
				}

				if (advancedGargoyle.isRespawned) //respawn gargoyle2;
				{
					int LoR = generateIntRandom(2, 1);
					advancedGargoyle.isRespawned = false;
					if (LoR == 1) advancedGargoyle.body.setPosition(generateIntRandom(500, 0), generateIntRandom(2300, 700));
					else if (LoR == 2) advancedGargoyle.body.setPosition(generateIntRandom(500, 1600), generateIntRandom(2300, 700));
					gargoyle2Array.push_back(advancedGargoyle);
				}
				gargoyle2Counter = 0; //gargoyle2 aggroed;
				for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
				{
					if (gargoyle2Array[gargoyle2Counter].isAggroed)
					{
						gargoyle2Array[gargoyle2Counter].action = generateIntRandom(2, 1);
						if (elapse[7].asMilliseconds() >= 10.f)
						{
							clock[7].restart();
							gargoyle2Array[gargoyle2Counter].updateAggroedFly(deltaTime, playerPosition);
						}
					}
					if (gargoyle2Array[gargoyle2Counter].action >= 2)
					{
						if (elapse[8].asSeconds() >= 0.8f)
						{
							clock[8].restart();
							if (playerPosition.x < gargoyle2Array[gargoyle2Counter].body.getPosition().x && abs(playerPosition.y - gargoyle2Array[gargoyle2Counter].body.getPosition().y) <= 40)
							{
								gargoyle2Bullet.direction = LEFT;
								gargoyle2Bullet.body.setPosition(gargoyle2Array[gargoyle2Counter].body.getPosition());
								gargoyle2BulletArray.push_back(gargoyle2Bullet);
								gargoyle2Array[gargoyle2Counter].direction = LEFT;
							}
							if (playerPosition.x > gargoyle2Array[gargoyle2Counter].body.getPosition().x && abs(playerPosition.y - gargoyle2Array[gargoyle2Counter].body.getPosition().y) <= 40)
							{
								gargoyle2Bullet.direction = RIGHT;
								gargoyle2Bullet.body.setPosition(gargoyle2Array[gargoyle2Counter].body.getPosition());
								gargoyle2BulletArray.push_back(gargoyle2Bullet);
								gargoyle2Array[gargoyle2Counter].direction = RIGHT;
							}
						}
					}
					gargoyle2Counter++;
				}
				gargoyle2Counter = 0; //gargoyle2 die;
				for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
				{
					if (gargoyle2Array[gargoyle2Counter].isDead)
					{
						coin.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y);
						coinArray.push_back(coin);
						if (chance(24) == 0)
						{
							hpp.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(19) == 0)
						{
							mpp.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(99) == 0)
						{
							Key.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						entityValue = gargoyle2Value;
						gargoyle2Array.erase(gargoyle2Iter);
						advancedGargoyle.isRespawned = true;
						break;
					}
					gargoyle2Counter++;
				}
				gargoyle2Counter = 0; //draw gargoyle1;
				for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
				{
					gargoyle2Array[gargoyle2Counter].updateFly(deltaTime);
					window.draw(gargoyle2Array[gargoyle2Counter].body);
					gargoyle2Counter++;
				}

				player.draw(window); //draw player;

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

			//stage 3//
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
					coinArray[coinCounter].lifetime++;
					if (coinArray[coinCounter].lifetime >= 500)
					{
						coinArray[coinCounter].lifetime = 0;
						coinArray[coinCounter].destroy = true;
					}
					coinCounter++;
				}
				hppCounter = 0;
				for (hppIter = hppArray.begin();hppIter != hppArray.end();hppIter++)
				{
					hppArray[hppCounter].update(deltaTime);
					window.draw(hppArray[hppCounter].body);
					hppArray[hppCounter].lifetime++;
					if (hppArray[hppCounter].lifetime >= 500)
					{
						hppArray[hppCounter].lifetime = 0;
						hppArray[hppCounter].destroy = true;
					}
					hppCounter++;
				}
				mppCounter = 0;
				for (mppIter = mppArray.begin();mppIter != mppArray.end();mppIter++)
				{
					mppArray[mppCounter].update(deltaTime);
					window.draw(mppArray[mppCounter].body);
					mppArray[mppCounter].lifetime++;
					if (mppArray[mppCounter].lifetime >= 500)
					{
						mppArray[mppCounter].lifetime = 0;
						mppArray[mppCounter].destroy = true;
					}
					mppCounter++;
				}
				keyCounter = 0;
				for (keyIter = keyArray.begin();keyIter != keyArray.end();keyIter++)
				{
					keyArray[keyCounter].update(deltaTime);
					window.draw(keyArray[keyCounter].body);
					keyArray[keyCounter].lifetime++;
					if (keyArray[keyCounter].lifetime >= 1800)
					{
						keyArray[keyCounter].lifetime = 0;
						keyArray[keyCounter].destroy = true;
					}
					keyCounter++;
				}

				//draw entities;
				if (normalTitan.isRespawned) //respawn titan1;
				{
					normalTitan.isRespawned = false;
					titan1Array.push_back(normalTitan);
					normalTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
				}
				titan1Counter = 0; //titan1 hit;
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
				titan1Counter = 0; //titan1	aggroed;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					if (elapse[3].asSeconds() >= 0.02f)
					{
						clock[3].restart();
						if (titan1Array[titan1Counter].isAggroed)
						{
							titan1Array[titan1Counter].action = 1;
							titan1Array[titan1Counter].updateAggrovated(deltaTime, playerPosition);
						}
					}
					titan1Counter++;
				}
				titan1Counter = 0; //titan1 die;
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
						if (chance(69) == 0)
						{
							Key.body.setPosition(titan1Array[titan1Counter].body.getPosition().x, titan1Array[titan1Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						entityValue = titan1Value;
						titan1Array.erase(titan1Iter);
						normalTitan.isRespawned = true;
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

				if (advancedTitan.isRespawned) //respawn titan2;
				{
					advancedTitan.isRespawned = false;
					titan2Array.push_back(advancedTitan);
					advancedTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
				}
				titan2Counter = 0; //titan2 hit;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					collider titan2Collision = titan2Array[titan2Counter].getCollider();
					for (int i = 0; i < blockS.size(); i++) blockS[i].getCollider().checkCollider(titan2Collision, 1.0f);

					if (player.body.getGlobalBounds().intersects(titan2Array[titan2Counter].body.getGlobalBounds()))
					{
						player.hurt();
						if (elapse[1].asSeconds() >= 0.5f)
						{
							clock[1].restart();
							int damage = titan2Array[titan2Counter].damage;
							dmgDp.text.setString("-" + to_string(damage));
							dmgDp.text.setPosition(playerPosition);
							dmgArray.push_back(dmgDp);
							if (!unlimitedHealthCheat) playerHP -= damage;
						}
					}
					titan2Counter++;
				}
				titan2Counter = 0; //titan2	aggroed;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					if (titan2Array[titan2Counter].isAggroed)
					{
						titan2Array[titan2Counter].action = generateIntRandom(2, 1);
						if (elapse[3].asSeconds() >= 0.02f)
						{
							clock[3].restart();
							titan2Array[titan2Counter].updateAggrovated(deltaTime, playerPosition);
						}
					}
					if (titan2Array[titan2Counter].action >= 2)
					{
						if (elapse[4].asSeconds() >= 0.5f)
						{
							clock[4].restart();
							if (playerPosition.x < titan2Array[titan2Counter].body.getPosition().x && abs(playerPosition.y - titan2Array[titan2Counter].body.getPosition().y) <= 40)
							{
								titan2Bullet.direction = LEFT;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = LEFT;
								advancedTitan.shoot = true;
							}
							if (playerPosition.x > titan2Array[titan2Counter].body.getPosition().x && abs(playerPosition.y - titan2Array[titan2Counter].body.getPosition().y) <= 40)
							{
								titan2Bullet.direction = RIGHT;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = RIGHT;
								advancedTitan.shoot = true;
							}
							if (playerPosition.y < titan2Array[titan2Counter].body.getPosition().y && abs(playerPosition.x - titan2Array[titan2Counter].body.getPosition().x) <= 40)
							{
								titan2Bullet.direction = UP;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = UP;
								advancedTitan.shoot = true;
							}
							if (playerPosition.y > titan2Array[titan2Counter].body.getPosition().y && abs(playerPosition.x - titan2Array[titan2Counter].body.getPosition().x) <= 40)
							{
								titan2Bullet.direction = DOWN;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = DOWN;
								advancedTitan.shoot = true;
							}
						}
					}
					titan2Counter++;
				}
				titan2Counter = 0; //titan2 die;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					if (titan2Array[titan2Counter].isDead)
					{
						coin.body.setPosition(titan2Array[titan2Counter].body.getPosition());
						coinArray.push_back(coin);
						if (chance(9) == 0)
						{
							hpp.body.setPosition(titan2Array[titan2Counter].body.getPosition().x + 25.f, titan2Array[titan2Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(4) == 0)
						{
							mpp.body.setPosition(titan2Array[titan2Counter].body.getPosition().x - 25.f, titan2Array[titan2Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(39) == 0)
						{
							Key.body.setPosition(titan2Array[titan2Counter].body.getPosition().x, titan2Array[titan2Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						entityValue = titan2Value;
						titan2Array.erase(titan2Iter);
						advancedTitan.isRespawned = true;
						break;
					}
					titan2Counter++;
				}
				titan2Counter = 0; //draw titan2;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					titan2Array[titan2Counter].updateWalk(deltaTime);
					window.draw(titan2Array[titan2Counter].body);
					titan2Counter++;
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
				boss.updateStill(deltaTime);

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
				boss.draw(window);
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

				//draw background;
				store.draw(window);

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
				playerMP += 0.5f * deltaTime;
				if (player.hp <= 0) isPlayerDead = true;

				//bullet events;
				if (wandLevel != 0) //player's bullets;
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
							gargoyle1Counter = 0; //gargoyle1 got hit;
							for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(gargoyle1Array[gargoyle1Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 3.f);
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(gargoyle1Array[gargoyle1Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									gargoyle1Array[gargoyle1Counter].hp -= damage;
									if (gargoyle1Array[gargoyle1Counter].hp <= 0.f)
									{
										gargoyle1Array[gargoyle1Counter].isDead = true;
										playerScore += 50;
									}
									gargoyle1Array[gargoyle1Counter].isAggroed = true;
								}
								gargoyle1Counter++;
							}

							gargoyle2Counter = 0; //gargoyle1 got hit;
							for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(gargoyle2Array[gargoyle2Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 4.f);
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(gargoyle2Array[gargoyle2Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									gargoyle2Array[gargoyle2Counter].hp -= damage;
									if (gargoyle2Array[gargoyle2Counter].hp <= 0.f)
									{
										gargoyle2Array[gargoyle2Counter].isDead = true;
										playerScore += 200;
									}
									gargoyle2Array[gargoyle2Counter].isAggroed = true;
								}
								gargoyle2Counter++;
							}
						}
						if (state == SKY)
						{
							titan1Counter = 0; //titan1 got hit;
							for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(titan1Array[titan1Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
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
									titan1Array[titan1Counter].isAggroed = true;
								}
								titan1Counter++;
							}

							titan2Counter = 0; //titan2 got hit;
							for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(titan2Array[titan2Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 6.f);
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(titan2Array[titan2Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									titan2Array[titan2Counter].hp -= damage;
									if (titan2Array[titan2Counter].hp <= 0.f)
									{
										titan2Array[titan2Counter].isDead = true;
										playerScore += 1500;
									}
									titan2Array[titan2Counter].isAggroed = true;
								}
								titan2Counter++;
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

				gargoyle1BulletCounter = 0; //gargoyle1's bullets hit player;
				for (gargoyle1BulletIter = gargoyle1BulletArray.begin(); gargoyle1BulletIter != gargoyle1BulletArray.end();gargoyle1BulletIter++)
				{
					if (gargoyle1BulletArray[gargoyle1BulletCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						int damage = gargoyle1BulletArray[gargoyle1BulletCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						playerHP -= gargoyle1Bullet.damage;
						gargoyle1BulletArray.erase(gargoyle1BulletIter);
						break;
					}
					gargoyle1BulletCounter++;
				}
				gargoyle1BulletCounter = 0; //draw gargoyle1's bullets;
				for (gargoyle1BulletIter = gargoyle1BulletArray.begin(); gargoyle1BulletIter != gargoyle1BulletArray.end();gargoyle1BulletIter++)
				{
					gargoyle1BulletArray[gargoyle1BulletCounter].update(deltaTime);
					window.draw(gargoyle1BulletArray[gargoyle1BulletCounter].body);
					gargoyle1BulletCounter++;
				}

				gargoyle2BulletCounter = 0; //gargoyle2's bullets hit player;
				for (gargoyle2BulletIter = gargoyle2BulletArray.begin(); gargoyle2BulletIter != gargoyle2BulletArray.end();gargoyle2BulletIter++)
				{
					if (gargoyle2BulletArray[gargoyle2BulletCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						int damage = gargoyle2BulletArray[gargoyle2BulletCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						playerHP -= gargoyle1Bullet.damage;
						gargoyle2BulletArray.erase(gargoyle2BulletIter);
						break;
					}
					gargoyle2BulletCounter++;
				}
				gargoyle2BulletCounter = 0; //draw gargoyle2's bullets;
				for (gargoyle2BulletIter = gargoyle2BulletArray.begin(); gargoyle2BulletIter != gargoyle2BulletArray.end();gargoyle2BulletIter++)
				{
					gargoyle2BulletArray[gargoyle2BulletCounter].update(deltaTime);
					window.draw(gargoyle2BulletArray[gargoyle2BulletCounter].body);
					gargoyle2BulletCounter++;
				}

				titan2BulletCounter = 0; //titan2's bullets hit player;
				for (titan2BulletIter = titan2BulletArray.begin(); titan2BulletIter != titan2BulletArray.end();titan2BulletIter++)
				{
					if (titan2BulletArray[titan2BulletCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						int damage = titan2BulletArray[titan2BulletCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						playerHP -= titan2Bullet.damage;
						titan2BulletArray.erase(titan2BulletIter);
						break;
					}
					titan2BulletCounter++;
				}
				titan2BulletCounter = 0; //draw titan2's bullets;
				for (titan2BulletIter = titan2BulletArray.begin(); titan2BulletIter != titan2BulletArray.end();titan2BulletIter++)
				{
					titan2BulletArray[titan2BulletCounter].update(deltaTime);
					window.draw(titan2BulletArray[titan2BulletCounter].body);
					titan2BulletCounter++;
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
						coinArray[coinCounter].destroy = true;
					}
					if (coinArray[coinCounter].destroy)
					{
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
						hppDp.text.setString("+1 HEALTH POTION");
						hppDp.text.setPosition(hppArray[hppCounter].body.getPosition());
						hppPickUpArray.push_back(hppDp);
						hppArray[hppCounter].destroy = true;
					}
					if (hppArray[hppCounter].destroy)
					{
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
						mppDp.text.setString("+1 MANA POTION");
						mppDp.text.setPosition(mppArray[mppCounter].body.getPosition());
						mppPickUpArray.push_back(mppDp);
						mppArray[mppCounter].destroy = true;
					}
					if (mppArray[mppCounter].destroy)
					{
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
						keyDp.text.setString("+1 KEY");
						keyDp.text.setPosition(keyArray[keyCounter].body.getPosition());
						keyPickUpArray.push_back(keyDp);
						keyArray[keyCounter].destroy = true;
					}
					if (keyArray[keyCounter].destroy)
					{
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
				hppPickUpCounter = 0;
				for (hppPickUpIter = hppPickUpArray.begin();hppPickUpIter != hppPickUpArray.end();hppPickUpIter++)
				{
					hppPickUpArray[hppPickUpCounter].update(deltaTime);
					window.draw(hppPickUpArray[hppPickUpCounter].text);
					if (hppPickUpArray[hppPickUpCounter].destroy)
					{
						hppPickUpArray.erase(hppPickUpIter);
						break;
					}
					hppPickUpCounter++;
				}
				mppPickUpCounter = 0;
				for (mppPickUpIter = mppPickUpArray.begin();mppPickUpIter != mppPickUpArray.end();mppPickUpIter++)
				{
					mppPickUpArray[mppPickUpCounter].update(deltaTime);
					window.draw(mppPickUpArray[mppPickUpCounter].text);
					if (mppPickUpArray[mppPickUpCounter].destroy)
					{
						mppPickUpArray.erase(mppPickUpIter);
						break;
					}
					mppPickUpCounter++;
				}
				keyPickUpCounter = 0;
				for (keyPickUpIter = keyPickUpArray.begin();keyPickUpIter != keyPickUpArray.end();keyPickUpIter++)
				{
					keyPickUpArray[keyPickUpCounter].update(deltaTime);
					window.draw(keyPickUpArray[keyPickUpCounter].text);
					if (keyPickUpArray[keyPickUpCounter].destroy)
					{
						keyPickUpArray.erase(keyPickUpIter);
						break;
					}
					keyPickUpCounter++;
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
				if (Keyboard::isKeyPressed(Keyboard::Num1) && hpPotion != 0)
				{
					hpPotion--;
					playerHP += 200;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) && mpPotion != 0)
				{
					mpPotion--;
					playerMP += 50;
				}

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

			//pause//
			if (Keyboard::isKeyPressed(Keyboard::Escape)) isPause = true;
		}

		//pause menu//
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
					isPause = false;
					window.clear();
					state = MENU;
					wandLevel = 0;
					playerScore = 0;
					playerMoney = 0;
					playerHP = maxHP;
					playerMP = maxMP;
					hpPotion = 0;
					mpPotion = 0;
					key = 0;
				}
			}
		}

		//game over//
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
					hpPotion = 0;
					mpPotion = 0;
					key = 0;
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

		//display window//
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