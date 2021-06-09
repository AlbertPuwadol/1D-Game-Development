#define _CRT_SECURE_NO_WARNINGS
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Animation.h"
#include"Collision.h"
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
vector<pair<int, string>> scoreboard;

static const float view_height = 650.0f;
static const float view_width = 1280.0f;


int main()
{
	sf::Font font;
	font.loadFromFile("Kenney Mini Square.ttf");
	
	sf::Text Score("", font, 40);
	Score.setFillColor(sf::Color(255, 0, 0));

	//			RANDOM			//
	srand(time(NULL));

	//				GAMEPLAY				//
	bool life = false;
	bool menu = true;
	bool select = false;
	bool result = false;
	bool Name = false;
	bool high = false;

	sf::Sprite pause;
	sf::Texture pausePic;
	pausePic.loadFromFile("pause.png");
	pause.setScale(0.2f, 0.2f);
	pause.setPosition(840.0f, 10.0f);
	pause.setTexture(pausePic);

	unsigned long score = 0;
	char scores[100];
	int character = 0;

	sf::SoundBuffer sound;
	sf::Sound effect;
	sound.loadFromFile("jump.ogg");
	effect.setBuffer(sound);

	std::string yourname;
	sf::Text play;

	play.setFillColor(sf::Color(255,210,0));

	int d = 0;
	int l = 0;
	int k = 2;

	ofstream myFile;

	ifstream loadFile;
	loadFile.open("high score.txt");

	while (!loadFile.eof())
	{
		string tempName;
		int tempScore;
		loadFile >> tempName >> tempScore;
		cout << ">> \"" << tempName << "\" " << tempScore << endl;
		scoreboard.push_back({ tempScore,tempName });
	}
	sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());
	loadFile.close();
	

	//			floor		//
	float last_Position1 = -5200.0f;
	float last_Position2 = -5200.0f;



	//			BACKGROUND 1280X650			//
	sf::RenderWindow window(sf::VideoMode(1280, 650), "ALPHA JUMP", sf::Style::Close);

	sf::Image icon;
	icon.loadFromFile("logo.png");
	window.setIcon(100, 100, icon.getPixelsPtr());

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(view_width, view_height));
	sf::RectangleShape background(sf::Vector2f(view_width, view_height));
	sf::Texture bg;
	sf::Sprite checkUp;
	sf::Texture up;
	bg.loadFromFile("blue-bg.png");
	background.setPosition(0, 0);
	background.setTexture(&bg);
	up.loadFromFile("Up_blow.png");
	checkUp.setPosition(background.getPosition());
	checkUp.setTexture(up);


	//			PLAYER 80X110			//
	bool pressed = false;
	bool canJump = true;
	sf::Texture playerTexture;
	sf::Texture playerJump;
	sf::Sprite body;
	sf::Sprite buttom;
	sf::Sprite front;
	sf::Sprite above;
	sf::Texture lineFront;
	sf::Texture lineButtom;
	sf::Texture lineAbove;
	lineFront.loadFromFile("line_blow.png");
	lineButtom.loadFromFile("line2_blow.png");
	lineAbove.loadFromFile("line3_blow.png");
	sf::Vector2f v(0.0f, 0.0f);
	int i = 1;
	float g = 2.0f;
	unsigned int row = 0;
	unsigned long time = 0;
	int countJ = 0;
	playerTexture.loadFromFile("1_walk.png");
	Animation player(&playerTexture, sf::Vector2u(2, 1), 0.25f);
	body.setPosition(150.0f, 400.0f);
	body.setTexture(playerTexture);
	front.setPosition(body.getPosition());
	buttom.setPosition(body.getPosition());
	above.setPosition(body.getPosition());
	front.setTexture(lineFront);
	buttom.setTexture(lineButtom);
	above.setTexture(lineAbove);

	//			SET GROUND 160X160			//
	int map = 0;
	int ground = 0;
	sf::Sprite ground1;

	sf::Sprite ground2;

	sf::Texture gn;
	sf::Texture gn2;
	sf::Texture gn3;
	sf::Texture gn4;
	sf::Texture gn5;
	sf::Texture gn6;
	sf::Texture gn7;
	sf::Texture gn8;
	sf::Texture gn9;
	sf::Texture gn10;
	
	gn.loadFromFile("map.png");
	gn2.loadFromFile("map2.png");
	gn3.loadFromFile("map3.png");
	gn4.loadFromFile("map4.png");
	gn5.loadFromFile("map5.png");
	gn6.loadFromFile("map6.png");
	gn7.loadFromFile("map7.png");
	gn8.loadFromFile("map8.png");
	gn9.loadFromFile("map9.png");
	gn10.loadFromFile("map10.png");

	ground1.setPosition(0.0f, 0.0f );
	ground2.setPosition(5200.0f, 0.0f);
	
	ground = rand() % 10;
	switch (ground)
	{
	case 0:
		ground1.setTexture(gn);
		break;
	case 1:
		ground1.setTexture(gn2);
		break;
	case 2:
		ground1.setTexture(gn3);
		break;
	case 3:
		ground1.setTexture(gn4);
		break;
	case 4:
		ground1.setTexture(gn5);
		break;
	case 5:
		ground1.setTexture(gn6);
		break;
	case 6:
		ground1.setTexture(gn7);
		break;
	case 7:
		ground1.setTexture(gn8);
		break;
	case 8:
		ground1.setTexture(gn9);
		break;
	case 9:
		ground1.setTexture(gn10);

		ground2.setTexture(gn2);
	}

	ground = rand() % 10;
	switch (ground)
	{
	case 0:
		ground2.setTexture(gn);
		break;
	case 1:
		ground2.setTexture(gn2);
		break;
	case 2:
		ground2.setTexture(gn3);
		break;
	case 3:
		ground2.setTexture(gn4);
		break;
	case 4:
		ground2.setTexture(gn5);
		break;
	case 5:
		ground2.setTexture(gn6);
		break;
	case 6:
		ground2.setTexture(gn7);
		break;
	case 7:
		ground2.setTexture(gn8);
		break;
	case 8:
		ground2.setTexture(gn9);
		break;
	case 9:
		ground2.setTexture(gn10);
	}

	//				Scope				//
	sf::Sprite scope;
	sf::Texture sc;
	sc.loadFromFile("scope.png");
	scope.setTexture(sc);

	//				Rocket				//
	int randRocket = 10;
	int countR = 0;
	int r[10] = { 1,0,0,0,0,0,0,0,0,0 };
	int timer = 0;
	int j = 1;
	bool canShoot = false;
	sf::Sprite rocket;
	sf::Texture rk;
	rk.loadFromFile("rocket.png");
	rocket.setTexture(rk);

	sf::Vector2f velocity(0.0f, 0.0f);

	float speed = -400.0f;

	float deltaTime = 0.0f;
	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		if (deltaTime > 1.0f / 4.0f)
			deltaTime = 1.0f / 4.0f;

		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !pressed && canJump && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && life)
		{
			if (countJ > 0)
				canJump = false;
			else
				countJ++;
			v.y = -25.0f;
			pressed = true;
			switch (character)
			{
				case 1:
					playerJump.loadFromFile("1_jump.png");
					break;
				case 2:
					playerJump.loadFromFile("2_jump.png");
					break;
				case 3:
					playerJump.loadFromFile("3_jump.png");
					break;
				case 4:
					playerJump.loadFromFile("4_jump.png");
					break;
				case 5:
					playerJump.loadFromFile("5_jump.png");
			}
			
			body.setTexture(playerJump);
			effect.play();
			i = 0;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (Collision::PixelPerfectTest(buttom, ground1) || Collision::PixelPerfectTest(buttom, ground2)) && life)
		{
			pressed = true;
			switch (character)
			{
			case 1:
				playerJump.loadFromFile("1_slide.png");
				break;
			case 2:
				playerJump.loadFromFile("2_slide.png");
				break;
			case 3:
				playerJump.loadFromFile("3_slide.png");
				break;
			case 4:
				playerJump.loadFromFile("4_slide.png");
				break;
			case 5:
				playerJump.loadFromFile("5_slide.png");
			}
			body.setTexture(playerJump);
			i = 1;
			front.setPosition(body.getPosition().x, body.getPosition().y + 40.0f);
			above.setPosition(body.getPosition().x, body.getPosition().y + 40.0f);
			//printf("%d\n", i);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && menu && !pressed)
		{
			pressed = true;
			menu = false;
			select = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && select && !pressed)
		{
			pressed = true;
			select = false;
			menu = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && life && !pressed)
		{
			pressed = true;
			life = false;
			menu = true;
			yourname.clear();
			play.setString(yourname);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && menu && !pressed)
		{
			pressed = true;
			menu = false;
			high = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && high && !pressed)
		{
			pressed = true;
			high = false;
			menu = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && select && !pressed)
		{

			d = 0;
			pressed = true;
			//printf("restart\n");
			select = false;
			Name = true;
			character = 1;


			//			Set New Character		//
			playerTexture.loadFromFile("1_walk.png");
			body.setPosition(150.0f, 400.0f);
			body.setTexture(playerTexture);
			front.setPosition(body.getPosition());
			buttom.setPosition(body.getPosition());
			above.setPosition(body.getPosition());

			//			Set New Rocket			//
			rocket.setPosition(1280.0f, 0.0f);

			//			Set Start Value			//
			yourname.clear();
			play.setString(yourname);
			score = 0;
			randRocket = 10;
			countR = 0;
			int r[10] = { 1,0,0,0,0,0,0,0,0,0 };
			timer = 0;
			j = 1;
			canShoot = false;
			speed = -400.0f;
			map = 0;
			ground = 0;
			i = 1;
			g = 2.0f;
			row = 0;
			time = 0;
			countJ = 0;
			pressed = false;
			canJump = true;
			last_Position1 = -5200.0f;
			last_Position2 = -5200.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && select && !pressed)
		{
			d = 0;
			pressed = true;
			//printf("restart\n");
			select = false;
			Name = true;
			character = 2;


			//			Set New Character		//
			playerTexture.loadFromFile("2_walk.png");
			body.setPosition(150.0f, 400.0f);
			body.setTexture(playerTexture);
			front.setPosition(body.getPosition());
			buttom.setPosition(body.getPosition());
			above.setPosition(body.getPosition());

			//			Set New Rocket			//
			rocket.setPosition(1280.0f, 0.0f);

			//			Set Start Value			//
			yourname.clear();
			play.setString(yourname);
			score = 0;
			randRocket = 10;
			countR = 0;
			int r[10] = { 1,0,0,0,0,0,0,0,0,0 };
			timer = 0;
			j = 1;
			canShoot = false;
			speed = -400.0f;
			map = 0;
			ground = 0;
			i = 1;
			g = 2.0f;
			row = 0;
			time = 0;
			countJ = 0;
			pressed = false;
			canJump = true;
			last_Position1 = -5200.0f;
			last_Position2 = -5200.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && select && !pressed)
		{
			d = 0;
			pressed = true;
			//printf("restart\n");
			select = false;
			Name = true;
			character = 3;


			//			Set New Character		//
			playerTexture.loadFromFile("3_walk.png");
			body.setPosition(150.0f, 400.0f);
			body.setTexture(playerTexture);
			front.setPosition(body.getPosition());
			buttom.setPosition(body.getPosition());
			above.setPosition(body.getPosition());

			//			Set New Rocket			//
			rocket.setPosition(1280.0f, 0.0f);

			//			Set Start Value			//
			yourname.clear();
			play.setString(yourname);
			score = 0;
			randRocket = 10;
			countR = 0;
			int r[10] = { 1,0,0,0,0,0,0,0,0,0 };
			timer = 0;
			j = 1;
			canShoot = false;
			speed = -400.0f;
			map = 0;
			ground = 0;
			i = 1;
			g = 2.0f;
			row = 0;
			time = 0;
			countJ = 0;
			pressed = false;
			canJump = true;
			last_Position1 = -5200.0f;
			last_Position2 = -5200.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && select && !pressed)
		{
			d = 0;
			pressed = true;
			//printf("restart\n");
			select = false;
			Name = true;
			character = 4;


			//			Set New Character		//
			playerTexture.loadFromFile("4_walk.png");
			body.setPosition(150.0f, 400.0f);
			body.setTexture(playerTexture);
			front.setPosition(body.getPosition());
			buttom.setPosition(body.getPosition());
			above.setPosition(body.getPosition());

			//			Set New Rocket			//
			rocket.setPosition(1280.0f, 0.0f);

			//			Set Start Value			//
			yourname.clear();
			play.setString(yourname);
			score = 0;
			randRocket = 10;
			countR = 0;
			int r[10] = { 1,0,0,0,0,0,0,0,0,0 };
			timer = 0;
			j = 1;
			canShoot = false;
			speed = -400.0f;
			map = 0;
			ground = 0;
			i = 1;
			g = 2.0f;
			row = 0;
			time = 0;
			countJ = 0;
			pressed = false;
			canJump = true;
			last_Position1 = -5200.0f;
			last_Position2 = -5200.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && select && !pressed)
		{
			d = 0;
			pressed = true;
			//printf("restart\n");
			select = false;
			Name = true;
			character = 5;


			//			Set New Character		//
			playerTexture.loadFromFile("5_walk.png");
			body.setPosition(150.0f, 400.0f);
			body.setTexture(playerTexture);
			front.setPosition(body.getPosition());
			buttom.setPosition(body.getPosition());
			above.setPosition(body.getPosition());

			//			Set New Rocket			//
			rocket.setPosition(1280.0f, 0.0f);

			//			Set Start Value			//
			yourname.clear();
			play.setString(yourname);
			score = 0;
			randRocket = 10;
			countR = 0;
			int r[10] = { 1,0,0,0,0,0,0,0,0,0 };
			timer = 0;
			j = 1;
			canShoot = false;
			speed = -400.0f;
			map = 0;
			ground = 0;
			i = 1;
			g = 2.0f;
			row = 0;
			time = 0;
			countJ = 0;
			pressed = false;
			canJump = true;
			last_Position1 = -5200.0f;
			last_Position2 = -5200.0f;
		}

		if (evnt.type == sf::Event::KeyReleased)
		{
			pressed = false;
			//printf("%d\n", i);
		}

		if (life && l == 0)
		{
			//			Set New Ground			//
			ground1.setPosition(0.0f, 0.0f);
			ground2.setPosition(5200.0f, 0.0f);
			ground1.setTexture(gn);
			ground2.setTexture(gn2);
			l++;
		}
		

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		switch (character)
		{
		case 1:
			//			Check Fall/Death			//

			if (body.getPosition().y >= 550.0f && body.getPosition().y < 650.0f && life)
			{
				body.move(v);
				velocity.x = 0.0f;
				canJump = false;
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}
			else if (body.getPosition().y >= 650.0f && life)
			{
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
				life = false;
				menu = true;
				result = menu;
				k = 0;
			}

			//			Check Rocket Hit		//

			if (Collision::PixelPerfectTest(body, rocket) && life)
			{
				playerTexture.loadFromFile("1_hurt.png");
				body.setTexture(playerTexture);
				v.y = 0.0f;
				velocity.x = 0.0f;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
				life = false;
				menu = true;
				result = menu;
				k = 0;
			}

			//			Check Above				//

			if (Collision::PixelPerfectTest(above, ground1) && !Collision::PixelPerfectTest(buttom, ground1) && life )
			{
				v.y = g;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}

			if (Collision::PixelPerfectTest(above, ground2) && !Collision::PixelPerfectTest(buttom, ground2) && life)
			{
				v.y = g;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}

			if (Collision::PixelPerfectTest(body, checkUp) && !Collision::PixelPerfectTest(buttom, ground1) && !Collision::PixelPerfectTest(buttom, ground2) && life)
			{
				v.y = g;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}

			//			Check buttom			//

			if (Collision::PixelPerfectTest(buttom, ground1) && v.y >= 0.0f && life)
			{
				if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//printf("pass\n");
					i = 0;
					playerTexture.loadFromFile("1_walk.png");
					body.setTexture(playerTexture);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				countJ = 0;
				canJump = true;
				time = 0;
				v.y = 0.0f;
				velocity.x = speed;
			}
			else if (Collision::PixelPerfectTest(buttom, ground2) && v.y >= 0.0f && life)
			{
				if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//printf("pass\n");
					i = 0;
					playerTexture.loadFromFile("1_walk.png");
					body.setTexture(playerTexture);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				countJ = 0;
				canJump = true;
				time = 0;
				v.y = 0.0f;
				velocity.x = speed;
			}
			else if (life)
			{
				if (time % 8 == 0)
				{
					body.move(v);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
					if (v.y < 0)
						v.y += g;
					else
						v.y = 8 * g;
					if (v.y > 0 && i == 0)
					{
						playerTexture.loadFromFile("1_fall.png");
						body.setTexture(playerTexture);
						i++;
					}
				}
				time++;
			}


			//			Check front			//

			if (Collision::PixelPerfectTest(front, ground1) && life)
			{
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				velocity.x = 0.0f;
			}
			else if (Collision::PixelPerfectTest(front, ground2) && life)
			{
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				velocity.x = 0.0f;
			}
			else if (body.getPosition().y <= 550 && life)
			{
				velocity.x = speed;
			}

			//			Score				//
			if (!Collision::PixelPerfectTest(front, ground1) && !Collision::PixelPerfectTest(front, ground2) && life)
			{
				score++;
				sprintf(scores, "%d", score / 100);
				Score.setString(scores);
				Score.setPosition(10.0f, 10.0f);
				//printf("%d\n", score/100);
			}

			//			Increase Speed			//
			if (map % 5 == 0 && map != 0 && speed > -1000.0f && life)
			{
				if (j < 10)
				{
					r[j] = 1;
					j++;
					//printf("prob %d0%\n", j);
				}
				speed -= 100.0f;
				//printf("speed %.1f\n", speed);
				map++;
				//printf("map %d\n", map);
			}

			if (map == 3 && randRocket == 10 && life)
				canShoot = true;
			break;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case 2:
			//			Check Fall/Death			//

			if (body.getPosition().y >= 550.0f && body.getPosition().y < 650.0f && life)
			{
				body.move(v);
				velocity.x = 0.0f;
				canJump = false;
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}
			else if (body.getPosition().y >= 650.0f && life)
			{
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
				life = false;
				menu = true;
				result = menu;
				k = 0;
			}

			//			Check Rocket Hit		//

			if (Collision::PixelPerfectTest(body, rocket) && life)
			{
				playerTexture.loadFromFile("2_hurt.png");
				body.setTexture(playerTexture);
				v.y = 0.0f;
				velocity.x = 0.0f;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
				life = false;
				menu = true;
				result = menu;
				k = 0;
			}

			//			Check Above				//

			if (Collision::PixelPerfectTest(above, ground1) && !Collision::PixelPerfectTest(buttom, ground1) && life)
			{
				v.y = g;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}

			if (Collision::PixelPerfectTest(above, ground2) && !Collision::PixelPerfectTest(buttom, ground2) && life)
			{
				v.y = g;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}

			if (Collision::PixelPerfectTest(body, checkUp) && !Collision::PixelPerfectTest(buttom, ground1) && !Collision::PixelPerfectTest(buttom, ground2) && life)
			{
				v.y = g;
				body.move(v);
				front.setPosition(body.getPosition());
				buttom.setPosition(body.getPosition());
				above.setPosition(body.getPosition());
			}

			//			Check buttom			//

			if (Collision::PixelPerfectTest(buttom, ground1) && v.y >= 0.0f && life)
			{
				if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//printf("pass\n");
					i = 0;
					playerTexture.loadFromFile("2_walk.png");
					body.setTexture(playerTexture);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				countJ = 0;
				canJump = true;
				time = 0;
				v.y = 0.0f;
				velocity.x = speed;
			}
			else if (Collision::PixelPerfectTest(buttom, ground2) && v.y >= 0.0f && life)
			{
				if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//printf("pass\n");
					i = 0;
					playerTexture.loadFromFile("2_walk.png");
					body.setTexture(playerTexture);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				countJ = 0;
				canJump = true;
				time = 0;
				v.y = 0.0f;
				velocity.x = speed;
			}
			else if (life)
			{
				if (time % 8 == 0)
				{
					body.move(v);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
					if (v.y <= 0)
						v.y += g;
					else
						v.y = 8 * g;
					if (v.y > 0 && i == 0)
					{
						playerTexture.loadFromFile("2_fall.png");
						body.setTexture(playerTexture);
						i++;
					}
				}
				time++;
			}


			//			Check front			//

			if (Collision::PixelPerfectTest(front, ground1) && life)
			{
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				velocity.x = 0.0f;
			}
			else if (Collision::PixelPerfectTest(front, ground2) && life)
			{
				player.Update(row, deltaTime);
				body.setTextureRect(player.uvRect);
				velocity.x = 0.0f;
			}
			else if (body.getPosition().y <= 550 && life)
			{
				velocity.x = speed;
			}

			//			Score				//
			if (!Collision::PixelPerfectTest(front, ground1) && !Collision::PixelPerfectTest(front, ground2) && life)
			{
				score++;
				sprintf(scores, "%d", score / 100);
				Score.setString(scores);
				Score.setPosition(10.0f, 10.0f);
				//printf("%d\n", score/100);
			}

			//			Increase Speed			//
			if (map % 5 == 0 && map != 0 && speed > -1000.0f && life)
			{
				if (j < 10)
				{
					r[j] = 1;
					j++;
					//printf("prob %d0%\n", j);
				}
				speed -= 100.0f;
				//printf("speed %.1f\n", speed);
				map++;
				//printf("map %d\n", map);
			}

			if (map == 3 && randRocket == 10 && life)
				canShoot = true;
			break;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 3:
				//			Check Fall/Death			//

				if (body.getPosition().y >= 550.0f && body.getPosition().y < 650.0f && life)
				{
					body.move(v);
					velocity.x = 0.0f;
					canJump = false;
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}
				else if (body.getPosition().y >= 650.0f && life)
				{
					body.move(v);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
					life = false;
					menu = true;
					result = menu;
					k = 0;
				}

				//			Check Rocket Hit		//

				if (Collision::PixelPerfectTest(body, rocket) && life)
				{
					playerTexture.loadFromFile("3_hurt.png");
					body.setTexture(playerTexture);
					v.y = 0.0f;
					velocity.x = 0.0f;
					body.move(v);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
					life = false;
					menu = true;
					result = menu;
					k = 0;
				}

				//			Check Above				//

				if (Collision::PixelPerfectTest(above, ground1) && !Collision::PixelPerfectTest(buttom, ground1) && life)
				{
					v.y = g;
					body.move(v);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}

				if (Collision::PixelPerfectTest(above, ground2) && !Collision::PixelPerfectTest(buttom, ground2) && life)
				{
					v.y = g;
					body.move(v);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}

				if (Collision::PixelPerfectTest(body, checkUp) && !Collision::PixelPerfectTest(buttom, ground1) && !Collision::PixelPerfectTest(buttom, ground2) && life)
				{
					v.y = g;
					body.move(v);
					front.setPosition(body.getPosition());
					buttom.setPosition(body.getPosition());
					above.setPosition(body.getPosition());
				}

				//			Check buttom			//

				if (Collision::PixelPerfectTest(buttom, ground1) && v.y >= 0.0f && life)
				{
					if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						//printf("pass\n");
						i = 0;
						playerTexture.loadFromFile("3_walk.png");
						body.setTexture(playerTexture);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
					}
					player.Update(row, deltaTime);
					body.setTextureRect(player.uvRect);
					countJ = 0;
					canJump = true;
					time = 0;
					v.y = 0.0f;
					velocity.x = speed;
				}
				else if (Collision::PixelPerfectTest(buttom, ground2) && v.y >= 0.0f && life)
				{
					if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						//printf("pass\n");
						i = 0;
						playerTexture.loadFromFile("3_walk.png");
						body.setTexture(playerTexture);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
					}
					player.Update(row, deltaTime);
					body.setTextureRect(player.uvRect);
					countJ = 0;
					canJump = true;
					time = 0;
					v.y = 0.0f;
					velocity.x = speed;
				}
				else if (life)
				{
					if (time % 8 == 0)
					{
						body.move(v);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
						if (v.y <= 0)
							v.y += g;
						else
							v.y = 8 * g;
						if (v.y > 0 && i == 0)
						{
							playerTexture.loadFromFile("3_fall.png");
							body.setTexture(playerTexture);
							i++;
						}
					}
					time++;
				}


				//			Check front			//

				if (Collision::PixelPerfectTest(front, ground1) && life)
				{
					player.Update(row, deltaTime);
					body.setTextureRect(player.uvRect);
					velocity.x = 0.0f;
				}
				else if (Collision::PixelPerfectTest(front, ground2) && life)
				{
					player.Update(row, deltaTime);
					body.setTextureRect(player.uvRect);
					velocity.x = 0.0f;
				}
				else if (body.getPosition().y <= 550 && life)
				{
					velocity.x = speed;
				}

				//			Score				//
				if (!Collision::PixelPerfectTest(front, ground1) && !Collision::PixelPerfectTest(front, ground2) && life)
				{
					score++;
					sprintf(scores, "%d", score / 100);
					Score.setString(scores);
					Score.setPosition(10.0f, 10.0f);
					//printf("%d\n", score/100);
				}

				//			Increase Speed			//
				if (map % 5 == 0 && map != 0 && speed > -1000.0f && life)
				{
					if (j < 10)
					{
						r[j] = 1;
						j++;
						//printf("prob %d0%\n", j);
					}
					speed -= 100.0f;
					//printf("speed %.1f\n", speed);
					map++;
					//printf("map %d\n", map);
				}

				if (map == 3 && randRocket == 10 && life)
					canShoot = true;
				break;
				/////////////////////////////////////////////////////////////////////////////////////////
				case 4:
					//			Check Fall/Death			//

					if (body.getPosition().y >= 550.0f && body.getPosition().y < 650.0f && life)
					{
						body.move(v);
						velocity.x = 0.0f;
						canJump = false;
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
					}
					else if (body.getPosition().y >= 650.0f && life)
					{
						body.move(v);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
						life = false;
						menu = true;
						result = menu;
						k = 0;
					}

					//			Check Rocket Hit		//

					if (Collision::PixelPerfectTest(body, rocket) && life)
					{
						playerTexture.loadFromFile("4_hurt.png");
						body.setTexture(playerTexture);
						v.y = 0.0f;
						velocity.x = 0.0f;
						body.move(v);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
						life = false;
						menu = true;
						result = menu;
						k = 0;
					}

					//			Check Above				//

					if (Collision::PixelPerfectTest(above, ground1) && !Collision::PixelPerfectTest(buttom, ground1) && life)
					{
						v.y = g;
						body.move(v);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
					}

					if (Collision::PixelPerfectTest(above, ground2) && !Collision::PixelPerfectTest(buttom, ground2) && life)
					{
						v.y = g;
						body.move(v);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
					}

					if (Collision::PixelPerfectTest(body, checkUp) && !Collision::PixelPerfectTest(buttom, ground1) && !Collision::PixelPerfectTest(buttom, ground2) && life)
					{
						v.y = g;
						body.move(v);
						front.setPosition(body.getPosition());
						buttom.setPosition(body.getPosition());
						above.setPosition(body.getPosition());
					}

					//			Check buttom			//

					if (Collision::PixelPerfectTest(buttom, ground1) && v.y >= 0.0f && life)
					{
						if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							//printf("pass\n");
							i = 0;
							playerTexture.loadFromFile("4_walk.png");
							body.setTexture(playerTexture);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
						}
						player.Update(row, deltaTime);
						body.setTextureRect(player.uvRect);
						countJ = 0;
						canJump = true;
						time = 0;
						v.y = 0.0f;
						velocity.x = speed;
					}
					else if (Collision::PixelPerfectTest(buttom, ground2) && v.y >= 0.0f && life)
					{
						if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							//printf("pass\n");
							i = 0;
							playerTexture.loadFromFile("4_walk.png");
							body.setTexture(playerTexture);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
						}
						player.Update(row, deltaTime);
						body.setTextureRect(player.uvRect);
						countJ = 0;
						canJump = true;
						time = 0;
						v.y = 0.0f;
						velocity.x = speed;
					}
					else if (life)
					{
						if (time % 8 == 0)
						{
							body.move(v);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
							if (v.y <= 0)
								v.y += g;
							else
								v.y = 8 * g;
							if (v.y > 0 && i == 0)
							{
								playerTexture.loadFromFile("4_fall.png");
								body.setTexture(playerTexture);
								i++;
							}
						}
						time++;
					}


					//			Check front			//

					if (Collision::PixelPerfectTest(front, ground1) && life)
					{
						player.Update(row, deltaTime);
						body.setTextureRect(player.uvRect);
						velocity.x = 0.0f;
					}
					else if (Collision::PixelPerfectTest(front, ground2) && life)
					{
						player.Update(row, deltaTime);
						body.setTextureRect(player.uvRect);
						velocity.x = 0.0f;
					}
					else if (body.getPosition().y <= 550 && life)
					{
						velocity.x = speed;
					}

					//			Score				//
					if (!Collision::PixelPerfectTest(front, ground1) && !Collision::PixelPerfectTest(front, ground2) && life)
					{
						score++;
						sprintf(scores, "%d", score / 100);
						Score.setString(scores);
						Score.setPosition(10.0f, 10.0f);
						//printf("%d\n", score/100);
					}

					//			Increase Speed			//
					if (map % 5 == 0 && map != 0 && speed > -1000.0f && life)
					{
						if (j < 10)
						{
							r[j] = 1;
							j++;
							//printf("prob %d0%\n", j);
						}
						speed -= 100.0f;
						//printf("speed %.1f\n", speed);
						map++;
						//printf("map %d\n", map);
					}

					if (map == 3 && randRocket == 10 && life)
						canShoot = true;
					break;
					/////////////////////////////////////////////////////////////////////////////////////////
					case 5:
						//			Check Fall/Death			//

						if (body.getPosition().y >= 550.0f && body.getPosition().y < 650.0f && life)
						{
							body.move(v);
							velocity.x = 0.0f;
							canJump = false;
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
						}
						else if (body.getPosition().y >= 650.0f && life)
						{
							body.move(v);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
							life = false;
							menu = true;
							result = menu;
							k = 0;
						}

						//			Check Rocket Hit		//

						if (Collision::PixelPerfectTest(body, rocket) && life)
						{
							playerTexture.loadFromFile("5_hurt.png");
							body.setTexture(playerTexture);
							v.y = 0.0f;
							velocity.x = 0.0f;
							body.move(v);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
							life = false;
							menu = true;
							result = menu;
							k = 0;
						}

						//			Check Above				//

						if (Collision::PixelPerfectTest(above, ground1) && !Collision::PixelPerfectTest(buttom, ground1) && life)
						{
							v.y = g;
							body.move(v);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
						}

						if (Collision::PixelPerfectTest(above, ground2) && !Collision::PixelPerfectTest(buttom, ground2) && life)
						{
							v.y = g;
							body.move(v);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
						}

						if (Collision::PixelPerfectTest(body, checkUp) && !Collision::PixelPerfectTest(buttom, ground1) && !Collision::PixelPerfectTest(buttom, ground2) && life)
						{
							v.y = g;
							body.move(v);
							front.setPosition(body.getPosition());
							buttom.setPosition(body.getPosition());
							above.setPosition(body.getPosition());
						}

						//			Check buttom			//

						if (Collision::PixelPerfectTest(buttom, ground1) && v.y >= 0.0f && life)
						{
							if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
							{
								//printf("pass\n");
								i = 0;
								playerTexture.loadFromFile("5_walk.png");
								body.setTexture(playerTexture);
								front.setPosition(body.getPosition());
								buttom.setPosition(body.getPosition());
								above.setPosition(body.getPosition());
							}
							player.Update(row, deltaTime);
							body.setTextureRect(player.uvRect);
							countJ = 0;
							canJump = true;
							time = 0;
							v.y = 0.0f;
							velocity.x = speed;
						}
						else if (Collision::PixelPerfectTest(buttom, ground2) && v.y >= 0.0f && life)
						{
							if (i == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
							{
								//printf("pass\n");
								i = 0;
								playerTexture.loadFromFile("5_walk.png");
								body.setTexture(playerTexture);
								front.setPosition(body.getPosition());
								buttom.setPosition(body.getPosition());
								above.setPosition(body.getPosition());
							}
							player.Update(row, deltaTime);
							body.setTextureRect(player.uvRect);
							countJ = 0;
							canJump = true;
							time = 0;
							v.y = 0.0f;
							velocity.x = speed;
						}
						else if (life)
						{
							if (time % 8 == 0)
							{
								body.move(v);
								front.setPosition(body.getPosition());
								buttom.setPosition(body.getPosition());
								above.setPosition(body.getPosition());
								if (v.y <= 0)
									v.y += g;
								else
									v.y = 8 * g;
								if (v.y > 0 && i == 0)
								{
									playerTexture.loadFromFile("5_fall.png");
									body.setTexture(playerTexture);
									i++;
								}
							}
							time++;
						}


						//			Check front			//

						if (Collision::PixelPerfectTest(front, ground1) && life)
						{
							player.Update(row, deltaTime);
							body.setTextureRect(player.uvRect);
							velocity.x = 0.0f;
						}
						else if (Collision::PixelPerfectTest(front, ground2) && life)
						{
							player.Update(row, deltaTime);
							body.setTextureRect(player.uvRect);
							velocity.x = 0.0f;
						}
						else if (body.getPosition().y <= 550 && life)
						{
							velocity.x = speed;
						}

						//			Score				//
						if (!Collision::PixelPerfectTest(front, ground1) && !Collision::PixelPerfectTest(front, ground2) && life)
						{
							score++;
							sprintf(scores, "%d", score / 100);
							Score.setString(scores);
							Score.setPosition(10.0f, 10.0f);
							//printf("%d\n", score/100);
						}

						//			Increase Speed			//
						if (map % 5 == 0 && map != 0 && speed > -1000.0f && life)
						{
							if (j < 10)
							{
								r[j] = 1;
								j++;
								//printf("prob %d0%\n", j);
							}
							speed -= 100.0f;
							//printf("speed %.1f\n", speed);
							map++;
							//printf("map %d\n", map);
						}

						if (map == 3 && randRocket == 10 && life)
							canShoot = true;
			}
		//			move ground		//

		if (ground1.getPosition().x <= last_Position1)
		{
			ground = rand() % 10;
			switch (ground)
			{
			case 0:
				ground1.setTexture(gn);
				break;
			case 1:
				ground1.setTexture(gn2);
				break;
			case 2:
				ground1.setTexture(gn3);
				break;
			case 3:
				ground1.setTexture(gn4);
				break;
			case 4:
				ground1.setTexture(gn5);
				break;
			case 5:
				ground1.setTexture(gn6);
				break;
			case 6:
				ground1.setTexture(gn7);
				break;
			case 7:
				ground1.setTexture(gn8);
				break;
			case 8:
				ground1.setTexture(gn9);
				break;
			case 9:
				ground1.setTexture(gn10);
			}
			last_Position1 = ground1.getPosition().x;
			ground1.setPosition(10400.0f + last_Position1 , 0.0f);
			map++;
			//printf("map %d\n", map);
		}			

		if (ground2.getPosition().x <= last_Position2)
		{
			ground = rand() % 10;
			switch (ground)
			{
			case 0:
				ground2.setTexture(gn);
				break;
			case 1:
				ground2.setTexture(gn2);
				break;
			case 2:
				ground2.setTexture(gn3);
				break;
			case 3:
				ground2.setTexture(gn4);
				break;
			case 4:
				ground2.setTexture(gn5);
				break;
			case 5:
				ground2.setTexture(gn6);
				break;
			case 6:
				ground2.setTexture(gn7);
				break;
			case 7:
				ground2.setTexture(gn8);
				break;
			case 8:
				ground2.setTexture(gn9);
				break;
			case 9:
				ground2.setTexture(gn10);
			}
			last_Position2 = ground2.getPosition().x;
			ground2.setPosition(10400.0f + last_Position2 , 0.0f);
			map++;
			//printf("map %d\n", map);
		}

		
			ground1.move(velocity * deltaTime);
			ground2.move(velocity * deltaTime);
		
		

		view.setCenter(background.getSize() / 2.0f);
		

		window.clear();
		window.setView(view);

		window.draw(background);

		window.draw(ground1);
		window.draw(ground2);

		


		if (life)
		{
			Score.setCharacterSize(40);
			Score.setFillColor(sf::Color(255, 0, 0));
			window.draw(Score);
			window.draw(pause);
		}
			

		//					Draw Body					//
		if(life)
		{ 
			window.draw(body);
		}
			

		//				Draw Scope & Rocket				//

		if (canShoot == true && life)
		{
			if (countR % 1000 == 0)
			{
				randRocket = rand() % 10;
				//printf("%d\n", r[randRocket]);
			}
			countR++;
		}

		if (r[randRocket] == 1 && randRocket < 10 && life)
		{
			//printf("scope\n");
			canShoot = false;
			if (timer <= 200)
			{
				sc.loadFromFile("scope.png");
				scope.setTexture(sc);
				scope.setPosition(1180.0f, body.getPosition().y);
				window.draw(scope);
				timer++;
			}
			else if (timer > 200 && timer <= 250)
			{
				sc.loadFromFile("scope_red.png");
				scope.setTexture(sc);
				window.draw(scope);
				timer++;
			}
			else
			{
				if (timer == 251)
				{
					rocket.setPosition(scope.getPosition().x + 20.0f, scope.getPosition().y + 45.0f);
					timer++;
				}
				sf::Vector2f vrocket;
				vrocket.x = 2*speed;
				rocket.move(vrocket * deltaTime);
				window.draw(rocket);
				if (rocket.getPosition().x <= -80)
				{
					timer = 0;
					randRocket = 10;
					canShoot = true;
				}

			}

		}


		/*window.draw(above);
		window.draw(front);
		window.draw(buttom);*/

		//					Menu				//
		if (menu)
		{
			//printf("start\n");
			velocity.x = -400.0f;
			if (result)
			{
				if (k == 0)
				{
					myFile.open("high score.txt", ios::out | ios::app);
					myFile << "\n" << yourname << " " << score/100;
					myFile.close();

					scoreboard.clear();

					ifstream loadFile;
					loadFile.open("high score.txt");

					while (!loadFile.eof()) 
					{
						string tempName;
						int tempScore;
						loadFile >> tempName >> tempScore;
						cout << ">> \"" << tempName << "\" " << tempScore << endl;
						scoreboard.push_back({ tempScore,tempName });
					}
					loadFile.close();
					sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());

					yourname = '\0';
					k++;
				}
				
				sf::Sprite rs;
				sf::Texture rsPic;
				rsPic.loadFromFile("score.png");
				rs.setScale(0.5f, 0.5f);
				rs.setPosition(400.0f, 250.0f);
				rs.setTexture(rsPic);
				window.draw(rs);
				Score.setFillColor(sf::Color(255, 210, 0));
				Score.setCharacterSize(80);
				Score.setPosition(520.0f, 310.0f);
				window.draw(Score);
			}
			sf::Sprite std;
			sf::Texture stdPic;
			stdPic.loadFromFile("std.png");
			std.setScale(0.6f, 0.6f);
			std.setPosition(800.0f, 0.0f);
			std.setTexture(stdPic);
			window.draw(std);
			sf::Sprite name;
			sf::Texture namePic;
			namePic.loadFromFile("name.png");
			name.setPosition(240.0f, 0.0f);
			name.setTexture(namePic);
			window.draw(name);
			sf::Sprite start;
			sf::Texture startPic;
			startPic.loadFromFile("start.png");
			start.setScale(0.25f, 0.25f);
			start.setPosition(410.0f, 570.0f);
			start.setTexture(startPic);
			window.draw(start);
			sf::Sprite h;
			sf::Texture hPic;
			hPic.loadFromFile("h.png");
			h.setScale(0.25f, 0.25f);
			h.setPosition(377.0f, 615.0f);
			h.setTexture(hPic);
			window.draw(h);
			sf::Sprite htp;
			sf::Texture htpPic;
			htpPic.loadFromFile("HTP.png");
			htp.setScale(0.5f, 0.5f);
			htp.setPosition(980.0f, 250.0f);
			htp.setTexture(htpPic);
			window.draw(htp);
		}

		//				Select Character			//
		if(select)
		{
			sf::Sprite Select;
			sf::Texture selectPic;
			selectPic.loadFromFile("select.png");
			Select.setPosition(0.0f, 0.0f);
			Select.setTexture(selectPic);
			window.draw(Select);
			sf::Sprite menu;
			sf::Texture menuPic;
			menuPic.loadFromFile("back1.png");
			menu.setScale(0.25f, 0.25f);
			menu.setPosition(330.0f, 615.0f);
			menu.setTexture(menuPic);
			window.draw(menu);
		}

		//					Delay Name				//
		if (d < 75)
			d++;

		//					Enter Name				//
		if (Name && d == 75)
		{
			velocity.x = -400.0f;
			sf::Sprite nme;
			sf::Texture nmePic;
			nmePic.loadFromFile("nameenter.png");
			nme.setScale(0.75f, 0.75f);
			nme.setPosition(325.0f, 85.0f);
			nme.setTexture(nmePic);
			window.draw(nme);
			if (evnt.type == sf::Event::TextEntered)
			{
				if (evnt.text.unicode == '\b' && !pressed && yourname.size() > 0 )
				{
					pressed = true;
 					yourname.erase(yourname.size() - 1, 1);
					play.setFont(font);
					play.setString(yourname);
				}
				else if(!pressed && (yourname.size() < 9) && evnt.key.code != sf::Keyboard::Enter && evnt.text.unicode != '\b')
				{
					pressed = true;
					sf::String name;
					yourname += static_cast<char>(evnt.text.unicode);
					name += static_cast<char>(evnt.text.unicode);
					if ((evnt.text.unicode < 128) && (yourname.size() < 9))
					{
						play.setFont(font);
						play.setString(yourname);
					}
				}
				play.setCharacterSize(80);
				play.setPosition(440.0f, 200.0f);
			}
			
			
			if (evnt.key.code == sf::Keyboard::Enter && !pressed && yourname.size() > 0)
			{
				pressed = true;
				play.setString(yourname);
				Name = false;
				life = true;
				l = 0;
			}
			

			if (evnt.type == sf::Event::KeyReleased)
			{
				pressed = false;
			}

			window.draw(play);
		}

		//					Show HighScore			//
		if (high)
		{
			sf::Sprite hsc;
			sf::Texture hscPic;
			hscPic.loadFromFile("high.png");
			hsc.setPosition(325.0f, 40.0f);
			hsc.setScale(0.75f, 0.75f);
			hsc.setTexture(hscPic);
			window.draw(hsc);
			int cnt = 0; 

			sf::Sprite menu;
			sf::Texture menuPic;
			menuPic.loadFromFile("back2.png");
			menu.setScale(0.25f, 0.25f);
			menu.setPosition(330.0f, 615.0f);
			menu.setTexture(menuPic);
			window.draw(menu);

			for (vector<pair<int, string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i) {
				++cnt;
				if (cnt > 5) break;                        
				sf::Text a, b;                                
				a.setString(to_string(i->first));         
				a.setFont(font);                        
				a.setCharacterSize(60);
				a.setFillColor(sf::Color(255, 210, 0));
				a.setPosition(900, 80 + (80 * cnt));      
				window.draw(a);                           
				b.setString(i->second);            
				b.setFont(font);                       
				b.setCharacterSize(60);   
				b.setFillColor(sf::Color(255, 210, 0));
				b.setPosition(300, 80 + (80 * cnt));      
				window.draw(b);                           
			}

		}

		window.display();
	}

	return 0;
}