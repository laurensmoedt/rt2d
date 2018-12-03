/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	iRight = 1;
	iDown = 0;

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


	// set position
	background->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	grid->position = Point2(SWIDTH / 9.3, SHEIGHT / 6.3);
	player1->position = Point2(SWIDTH / 9.3, SHEIGHT / 6.3);


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

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete grid;
	delete background;
	delete player1;
}

void MyScene::update(float deltaTime)
{


	// ###############################################################
	// Move players (Arrow up, down, left, right)
	// ###############################################################

	float speed = 100.0f; // 600 units / second

	// Right and down vector
	// Direction
	Vector2 direction = Vector2(iRight, iDown);

	if (input()->getKey(KeyCode::Up) && iDown != 1) {
		iRight = 0;
		iDown = -1;
	}
	if (input()->getKey(KeyCode::Down) && iDown != -1) {
		iRight = 0;
		iDown = 1;
	}
	if (input()->getKey(KeyCode::Right) && iRight != -1) {
		iDown = 0;
		iRight = 1;
	}
	if (input()->getKey(KeyCode::Left) && iRight != 1) {
		iDown = 0;
		iRight = -1;
	}

	direction.normalize();
	direction *= deltaTime * speed;
	player1->position += direction;


	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Rotate color
	// ###############################################################

	if (t.seconds() > 0.0333f) {
		RGBAColor color = background->sprite()->color;
		background->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}
}
