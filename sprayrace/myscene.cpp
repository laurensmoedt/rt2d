/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include "myscene.h"

using std::cout;

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	iright1 = 1;
	iright2 = 1;
	idown1 = 0;
	idown2 = 0;

	gridwidth = 60;
	gridheight = 30;
	cellwidth = 17;
	cellheight = 17;

	top_layer = 7; // 8 layers (0-7)

	for (unsigned int i = 0; i <= top_layer; i++) {
		MyEntity* layer = new MyEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	// create grid
	grid = new MyEntity();
	grid->addGrid("assets/gridBlock.tga", 1, 1, gridwidth, gridheight, cellwidth, cellheight);

	std::vector<Sprite*> spritebatch = grid->spritebatch();
	for (size_t i = 0; i < spritebatch.size(); i++)
	{
		spritebatch[i]->color = BLACK;
	}

	layers[1]->addChild(grid);

	// background
	background = new MyEntity();
	background->addSprite("assets/background.tga");
	background->sprite()->color = RED;
	layers[0]->addChild(background);

	//players
	player1 = new Player();
	player1->addSprite("assets/player1.tga");
	layers[2]->addChild(player1);

	player2 = new Player();
	player2->addSprite("assets/player2.tga");
	layers[2]->addChild(player2);


	// set position
	background->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	grid->position = Point2(SWIDTH / 9.3, SHEIGHT / 6.3);
	player1->position = Point2(SWIDTH / 9.3, SHEIGHT / 6.3);
	player2->position = Point2(SWIDTH / 9.3, SHEIGHT / 6.3);


}


MyScene::~MyScene()
{

	int ls = layers.size();
	for (int i=0; i<ls; i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = NULL;
	}

	layers.clear();

	// deconstruct and delete the Tree
	layers[0]->removeChild(background);
	layers[1]->removeChild(grid);
	layers[2]->removeChild(player1);
	layers[2]->removeChild(player2);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete grid;
	delete background;
	delete player1;
	delete player2;
}

void MyScene::update(float deltaTime)
{

	int p1x = player1->position.x - SWIDTH / 9.3;
	int p1y = player1->position.y - SHEIGHT / 6.3;

	int p2x = player2->position.x - SWIDTH / 9.3;
	int p2y = player2->position.y - SHEIGHT / 6.3;

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}
	// ###############################################################
	// Rotate background color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = background->sprite()->color;
		background->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}



		// ###############################################################
		// Move players (Arrow up, down, left, right)
		// ###############################################################

		float speed = 200.0f; // 600 units / second

		Vector2 directionp1 = Vector2(iright1, idown1);
		Vector2 directionp2 = Vector2(iright2, idown2);

		//player1
		if (input()->getKeyDown(KeyCode::Up) && idown1 != 1) {
			iright1 = 0;
			idown1 = -1;
		}
		else if (input()->getKeyDown(KeyCode::Down) && idown1 != -1) {
			iright1 = 0;
			idown1 = 1;
		}
		else if (input()->getKeyDown(KeyCode::Right) && iright1 != -1) {
			idown1 = 0;
			iright1 = 1;
		}
		else if (input()->getKeyDown(KeyCode::Left) && iright1 != 1) {
			idown1 = 0;
			iright1 = -1;
		}

		//player2
		if (input()->getKeyDown(KeyCode::W) && idown2 != 1) {
			iright2 = 0;
			idown2 = -1;
		}
		else if (input()->getKeyDown(KeyCode::S) && idown2 != -1) {
			iright2 = 0;
			idown2 = 1;
		}
		else if (input()->getKeyDown(KeyCode::D) && iright2 != -1) {
			idown2 = 0;
			iright2 = 1;
		}
		else if (input()->getKeyDown(KeyCode::A) && iright2 != 1) {
			idown2 = 0;
			iright2 = -1;
		}

		directionp1.normalize();
		directionp2.normalize();
		directionp1 *= deltaTime * speed;
		directionp2 *= deltaTime * speed;
		player1->position += directionp1;
		player2->position += directionp2;




		std::vector<Sprite*> spritebatch = grid->spritebatch();
		int counter = 0;
		for (int x=0; x<gridwidth; x++) {
			for (int y=0; y<gridheight ; y++) {
				Point2 pos = spritebatch[counter]->spriteposition;

				int halfwidth = cellwidth/2;
				int halfheight = cellheight/2;
				int left = pos.x - halfwidth;
				int right = pos.x + halfwidth;
				int top = pos.y - halfheight;
				int bottom = pos.y + halfheight;

				if ( p1x > left && p1x < right && p1y > top && p1y < bottom ) {
					spritebatch[counter]->color = GREEN;
				}
				if ( p2x > left && p2x < right && p2y > top && p2y < bottom ) {
					spritebatch[counter]->color = ORANGE;
				}
				counter++;
			}
		}
}
