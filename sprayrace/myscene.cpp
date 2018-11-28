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


	gridwidth = 24;
	gridheight = 14;
	cellwidth = 42;
	cellheight = 36;

	top_layer = 7; // 8 layers (0-7)

	for (unsigned int i = 0; i <= top_layer; i++) {
		MyEntity* layer = new MyEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	// create grid
	grid = new MyEntity();
	background = new MyEntity();

	grid->addGrid("assets/gridBlock.tga", 1, 1, gridwidth, gridheight, cellwidth, cellheight);
	background->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	grid->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	background->addSprite("assets/background1.tga");
	background->sprite()->color = RED;


	layers[1]->addChild(grid);
	layers[0]->addChild(background);
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
	layers[0]->removeChild(grid);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete grid;
}

void MyScene::update(float deltaTime)
{

	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 600.0f; // 600 units / second

	// Right and Down vector
	Point2 right = Point2(1, 0);
	Point2 up = Point2(0, 1);
	// Direction
	Vector2 direction = Vector2(0,0);

	if (input()->getKey(KeyCode::Up)) {
		direction -= up;
	}
	if (input()->getKey(KeyCode::Down)) {
		direction += up;
	}
	if (input()->getKey(KeyCode::Right)) {
		direction += right;
	}
	if (input()->getKey(KeyCode::Left)) {
		direction -= right;
	}
	direction.normalize();
	direction *= deltaTime * speed;
	camera()->position += direction;

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
