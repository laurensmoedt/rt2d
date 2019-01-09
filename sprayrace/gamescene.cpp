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
	// start the timer.
	t.start();

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
	top_layer = 7; // 8 layers (0-7)
	for (unsigned int i = 0; i <= top_layer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}
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

	//grid
	grid = new Grid();

	//players
	player1 = new Player();
	player1->sprite()->color = BLUE;

	player2 = new Player();
	player2->sprite()->color = ORANGE;

	//menu's
	endMenu = new EndMenu();

	//buttons
	restartButton = new Button("Restart", GRAY);
	restartButton->position = Point2(SWIDTH / 3, SHEIGHT / 3);
	restartButton->setButtonRun(std::bind(&GameScene::restart, this));

	//add to scene
	layers[0]->addChild(gameBackground);
	layers[0]->addChild(gridBackground);
	layers[1]->addChild(grid);
	layers[2]->addChild(player1);
	layers[2]->addChild(player2);

	//position
	gameBackground->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	gridBackground->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	player1->position = Point2(SWIDTH / 5.2, SHEIGHT / 2.14);
	player2->position = Point2(SWIDTH / 1.2, SHEIGHT / 2.14);
	endMenu->position = Point2(SWIDTH / 2, SHEIGHT / 2);
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
	// Rotate gridBackground color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = gridBackground->sprite()->color;
		gridBackground->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}



		// ###############################################################
		// Move players (player1: Arrow up, down, left, right
		// 				(player2: a, s, w, d)
		// ###############################################################

		float speed = 150.0f;

		Vector2 directionp1 = Vector2(iright1, idown1);
		Vector2 directionp2 = Vector2(iright2, idown2);


		//player1
		if (input()->getKey(KeyCode::Up) && idown1 != 1 && idown1 != -1) {
			dir1 = 1;
		}
		else if (input()->getKey(KeyCode::Down) && idown1 != -1 && idown1 != 1) {
			dir2 = 1;
		}
		else if (input()->getKey(KeyCode::Right) && iright1 != -1 && iright1 != 1) {
			dir3 = 1;
		}
		else if (input()->getKey(KeyCode::Left) && iright1 != 1 && iright1 != -1) {
			dir4 = 1;
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
		if (input()->getKeyDown(KeyCode::W) && idown2 != 1 && idown2 != -1) {
			dir1p2 = 1;
		}
		else if (input()->getKeyDown(KeyCode::S) && idown2 != -1 && idown2 != 1) {
			dir2p2 = 1;
		}
		else if (input()->getKeyDown(KeyCode::D) && iright2 != -1 && iright2 != 1) {
			dir3p2 = 1;
		}
		else if (input()->getKeyDown(KeyCode::A) && iright2 != 1 && iright2 != -1) {
			dir4p2 = 1;
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


				int quadwidth = grid->cellwidth/2;
				int quadheight = grid->cellheight/2;
				int left = pos.x - quadwidth;
				int right = pos.x + quadwidth;
				int top = pos.y - quadheight;
				int bottom = pos.y + quadheight;

				if (pos != p1lastSpritePos) {
					if (p1x > left && p1x < right && p1y > top && p1y < bottom) {
						if (spritebatch[counter]->color == ORANGE)
						{
							endScreen();
						}
						else if (spritebatch[counter]->color == BLUE)
						{
							endScreen();
						}
						else
						{
							spritebatch[counter]->color = BLUE;
							p1lastSpritePos = spritebatch[counter]->spriteposition;
						}
					}
				}

				if (pos != p2lastSpritePos)
				{
					if (p2x > left && p2x < right && p2y > top && p2y < bottom) {
						if (spritebatch[counter]->color == BLUE)
						{
							endScreen();
						}
						else if (spritebatch[counter]->color == ORANGE)
						{
							endScreen();
						}
						else
						{
							spritebatch[counter]->color = ORANGE;
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
			this->stop();
		}
		else if (p1x < 0)
		{
			this->stop();
		}
		else if (p1y < 0)
		{
			this->stop();
		}
		else if (p1x >= 1024)
		{
			this->stop();
		}
		else if (p1y >= 512)
		{
			this->stop();
		}
		//collision p2
		else if (p2x < 0)
		{
			this->stop();
		}
		else if (p2y < 0)
		{
			this->stop();
		}
		else if (p2x >= 1024)
		{
			this->stop();
		}
		else if (p2y >= 512)
		{
			this->stop();
		}
}
void GameScene::endScreen() {

	layers[3]->addChild(endMenu);
	text[1]->message("blue/orange won");
	text[1]->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	layers[3]->addChild(restartButton);
}

void GameScene::restart() {

}
