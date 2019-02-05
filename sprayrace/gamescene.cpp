/**
 * This class describes GameScene behavior.
 *
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include "gamescene.h"


GameScene::GameScene() : Scene()
{	

	//movements
	dir1 = 0;
	dir2 = 0;
	dir3 = 0;
	dir4 = 0;

	dir1p2 = 0;
	dir2p2 = 0;
	dir3p2 = 0;
	dir4p2 = 0;

	iright1 = 1;
	iright2 = -1;
	idown1 = 0;
	idown2 = 0;

	p1lastSpritePos = Point2(0,0);
	p2lastSpritePos = Point2(0, 0);


	//layers
	// layer 0 is for game background and grid background
	// layer 1 is for the grid
	// layer 2 is for both players
	// layer 3 is for the end menu and restart button
	top_layer = 7; // 8 layers (0-7)
	for (unsigned int i = 0; i <= top_layer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	//text layers
	// layer 1 is for the score of player 1
	// layer 2 is for the score of player 2
	// layer 3 is for the message when one player gets 5 points and wins
	for (unsigned int i = 0; i < 16; i++) {
		Text* line = new Text();
		line->scale = Point2(0.5f, 0.5f);
		
		text.push_back(line);
		layers[top_layer]->addChild(line);
	}

	// gridBackgrounds
	gridBackground = new BasicEntity();
	gridBackground->addSprite("assets/gridBackground.tga");
	gridBackground->sprite()->color = RED;

	gameBackground = new BasicEntity();
	gameBackground->addSprite("assets/gameBackground.tga");
	gameBackground->sprite()->color = RED;

	//grid
	grid = new Grid();

	//players
	player1 = new Player(NEONBLUE);
	player2 = new Player(NEONORANGE);
	player2->addSprite("assets/playerL.tga");
	player2->sprite()->color = NEONORANGE;

	//menu's
	endMenu = new EndMenu();

	//buttons
	startButton = new Button("START", WHITE);
	startButton->position = Point2(SWIDTH / 2, SHEIGHT / 3);
	startButton->setButtonRun(std::bind(&GameScene::startGame, this));

	restartButton = new Button("RESTART", WHITE);
	restartButton->position = Point2(SWIDTH / 3 - 80, SHEIGHT / 3);
	restartButton->setButtonRun(std::bind(&GameScene::restart, this));

	stopButton = new Button("QUIT", WHITE);
	stopButton->position = Point2(SWIDTH / 2, SHEIGHT / 3);
	stopButton->setButtonRun(std::bind(&GameScene::stopgame, this));
	stopButton->setTextOffset(-28);
	//score
	blueScore = 0;
	orangeScore = 0;


	//add to scene
	layers[0]->addChild(gameBackground);
	layers[0]->addChild(gridBackground);
	layers[1]->addChild(grid);
	layers[2]->addChild(player1);
	layers[2]->addChild(player2);
	layers[3]->addChild(startButton);

	//position
	gameBackground->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	gridBackground->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	player1->position = Point2(SWIDTH / 5.2, SHEIGHT / 2.14);
	player2->position = Point2(SWIDTH / 1.2, SHEIGHT / 2.14);
}


GameScene::~GameScene()
{

	// deconstruct and delete
	layers[0]->removeChild(gameBackground);
	layers[0]->removeChild(gridBackground);
	layers[1]->removeChild(grid);
	layers[2]->removeChild(player1);
	layers[2]->removeChild(player2);
	layers[3]->removeChild(endMenu);

	// delete from the heap (there was a 'new' in the constructor)
	delete gameBackground;
	delete gridBackground;
	delete grid;
	delete player1;
	delete player2;
	delete endMenu;
	delete restartButton;
	delete stopButton;
	delete startButton;

	int ts = text.size();
	for (int i = 0; i<ts; i++) {
		this->removeChild(text[i]);
		delete text[i];
		text[i] = nullptr;
	}
	text.clear();
}

void GameScene::update(float deltaTime)
{
	player1->sprite()->color = NEONBLUE;
	player2->sprite()->color = NEONORANGE;

	p1x = player1->position.x - SWIDTH / 9.4;
	p1y = player1->position.y - SHEIGHT / 6.4;

	p2x = player2->position.x - SWIDTH / 9.4;
	p2y = player2->position.y - SHEIGHT / 6.4;



	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}
	// ###############################################################
	// Rotate Backgrounds color
	// ###############################################################
	if (t.seconds() > 0.03f) {
		RGBAColor color = gameBackground->sprite()->color;
		gameBackground->sprite()->color = Color::rotate(color, 0.01f);
		gridBackground->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}



		// ###############################################################
		// Move players (player1: Arrow up, down, left, right
		// 				(player2: a, s, w, d)
		// ###############################################################

		Vector2 directionp1 = Vector2(iright1, idown1);
		Vector2 directionp2 = Vector2(iright2, idown2);


		//player1
		if (input()->getKey(KeyCode::W) && idown1 != 1 && idown1 != -1) {
			dir1 = 1;
			player1->addSprite("assets/playerU.tga");
			player1->sprite()->color = NEONBLUE;
		}
		else if (input()->getKey(KeyCode::S) && idown1 != -1 && idown1 != 1) {
			dir2 = 1;
			player1->addSprite("assets/playerD.tga");
			player1->sprite()->color = NEONBLUE;
		}
		else if (input()->getKey(KeyCode::D) && iright1 != -1 && iright1 != 1) {
			dir3 = 1;
			player1->addSprite("assets/playerR.tga");
			player1->sprite()->color = NEONBLUE;
		}
		else if (input()->getKey(KeyCode::A) && iright1 != 1 && iright1 != -1) {
			dir4 = 1;
			player1->addSprite("assets/playerL.tga");
			player1->sprite()->color = NEONBLUE;
		}

		if (dir1 == 1 && p1x % grid->cellwidth == 0)
		{
			idown1 = -1;
			iright1 = 0;
			dir1 = 0;
		}
		if (dir2 == 1 && p1x % grid->cellwidth == 0)
		{
			idown1 = 1;
			iright1 = 0;
			dir2 = 0;
		}
		if (dir3 == 1 && p1y % grid->cellwidth == 0)
		{
			idown1 = 0;
			iright1 = 1;
			dir3 = 0;
		}
		if (dir4 == 1 && p1y % grid->cellwidth == 0)
		{
			idown1 = 0;
			iright1 = -1;
			dir4 = 0;
		}

		//player2
		if (input()->getKeyDown(KeyCode::Up) && idown2 != 1 && idown2 != -1) {
			dir1p2 = 1;
			player2->addSprite("assets/playerU.tga");
			player2->sprite()->color = NEONORANGE;
		}
		else if (input()->getKeyDown(KeyCode::Down) && idown2 != -1 && idown2 != 1) {
			dir2p2 = 1;
			player2->addSprite("assets/playerD.tga");
			player2->sprite()->color = NEONORANGE;
		}
		else if (input()->getKeyDown(KeyCode::Right) && iright2 != -1 && iright2 != 1) {
			dir3p2 = 1;
			player2->addSprite("assets/playerR.tga");
			player2->sprite()->color = NEONORANGE;
		}
		else if (input()->getKeyDown(KeyCode::Left) && iright2 != 1 && iright2 != -1) {
			dir4p2 = 1;
			player2->addSprite("assets/playerL.tga");
			player2->sprite()->color = NEONORANGE;
		}

		if (dir1p2 == 1 && p2x % grid->cellwidth == 0)
		{
			idown2 = -1;
			iright2 = 0;
			dir1p2 = 0;
		}
		if (dir2p2 == 1 && p2x % grid->cellwidth == 0)
		{
			idown2 = 1;
			iright2 = 0;
			dir2p2 = 0;
		}
		if (dir3p2 == 1 && p2y % grid->cellheight == 0)
		{
			idown2 = 0;
			iright2 = 1;
			dir3p2 = 0;
		}
		if (dir4p2 == 1 && p2y % grid->cellheight == 0)
		{
			idown2 = 0;
			iright2 = -1;
			dir4p2 = 0;
		}

		directionp1 *= deltaTime * speed;
		directionp2 *= deltaTime * speed;
		player1->position += directionp1;
		player2->position += directionp2;



		// fill grid when a players moves over them
		std::vector<Sprite*> spritebatch = grid->spritebatch();
		int counter = 0;

		for (int x=0; x<grid->gridwidth; x++) {
			for (int y=0; y<grid->gridheight ; y++) {
				Point2 pos = spritebatch[counter]->spriteposition;


				int quadwidth = grid->cellwidth/4;
				int quadheight = grid->cellheight/4;
				int left = pos.x - quadwidth;
				int right = pos.x + quadwidth;
				int top = pos.y - quadheight;
				int bottom = pos.y + quadheight;

				if (pos != p1lastSpritePos) {
					if (p1x > left && p1x < right && p1y > top && p1y < bottom) {
						if (spritebatch[counter]->color == NEONORANGE)
						{
							orangeScore += 1;
							endScreen();
						}
						else if (spritebatch[counter]->color == NEONBLUE)
						{
							orangeScore += 1;
							endScreen();
						}
						else
						{
							spritebatch[counter]->color = NEONBLUE;
							p1lastSpritePos = spritebatch[counter]->spriteposition;
						}
					}
				}

				if (pos != p2lastSpritePos)
				{
					if (p2x > left && p2x < right && p2y > top && p2y < bottom) {
						if (spritebatch[counter]->color == NEONBLUE || spritebatch[counter]->color == NEONORANGE)
						{
							blueScore += 1;
							endScreen();
						}

						else
						{
							spritebatch[counter]->color = NEONORANGE;
							p2lastSpritePos = spritebatch[counter]->spriteposition;
						}
					}
				}
				counter++;

			}
		}

		//collision p1
		if (p1y == p2y && p1x == p2x)
		{
			endScreen();
		}
		else if (p1x < 0 || p1y < 0)
		{
			orangeScore += 1;
			endScreen();
		}
		else if (p1x >= 1024 || p1y >= 512)
		{
			orangeScore += 1;
			endScreen();
		}
		//collision p2
		else if (p2x < 0 || p2y < 0)
		{
			blueScore += 1;
			endScreen();
		}
		else if (p2x >= 1024 || p2y >= 512)
		{
			blueScore += 1;
			endScreen();
		}

		//displays score of both players
		text[4]->message("PLAYER 1", NEONBLUE);
		text[4]->scale = Point2(1.0f, 1.0f);
		text[4]->position = Point2(150, 30);
		std::stringstream scoreBlue;
		scoreBlue << "POINTS: " << blueScore;
		text[1]->message(scoreBlue.str(), NEONBLUE);
		text[1]->position = Point2(200, 70);

		text[5]->message("PLAYER 2", NEONORANGE);
		text[5]->scale = Point2(1.0f, 1.0f);
		text[5]->position = Point2(900, 30);
		std::stringstream scoreOrange;
		scoreOrange << "POINTS: " << orangeScore;
		text[2]->message(scoreOrange.str(), NEONORANGE);
		text[2]->position = Point2(950, 70);
}

void GameScene::endScreen() {
	player1->position = Point2(SWIDTH / 5.2, SHEIGHT / 2.14);
	player2->position = Point2(SWIDTH / 1.2, SHEIGHT / 2.14);
	std::vector<Sprite*> spritebatch = grid->spritebatch();
	for (size_t i = 0; i < spritebatch.size(); i++)
	{
		spritebatch[i]->color = BLACK;
	}
	speed = 0.0f;
	layers[3]->addChild(endMenu);
	text[3]->position = Point2(200, 400);
	text[3]->scale = Point2(1.0f, 1.0f);
	if (blueScore == 5)
	{
		text[3]->message("BLUE HAS WON THE MATCH!!!", NEONBLUE);
		layers[3]->addChild(stopButton);
	}
	else if (orangeScore == 5)
	{
		text[3]->message("ORANGE HAS WON THE MATCH!!!", NEONORANGE);
		layers[3]->addChild(stopButton);
	}
	else
	{
		layers[3]->addChild(restartButton);
		layers[3]->addChild(stopButton);
	}

}

void GameScene::restart() {

	layers[3]->removeChild(endMenu);
	layers[3]->removeChild(restartButton);
	layers[3]->removeChild(stopButton);
	speed = 750.0f;
	iright1 = 1;
	iright2 = -1;
	idown1 = 0;
	idown2 = 0;
	player1->addSprite("assets/playerR.tga");
	player2->addSprite("assets/playerL.tga");
}

void GameScene::stopgame() {
	this->stop();
}

void GameScene::startGame() {
	speed = 350.0f;
	t.start();
	layers[3]->removeChild(startButton);
}
