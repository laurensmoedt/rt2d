/**
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H


#include <vector>
#include <rt2d/timer.h>
#include <rt2d/scene.h>
#include "myentity.h"
#include "player.h"

/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{

public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:

	MyEntity* background;
	Player* player1;
	Player* player2;
	MyEntity* grid;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;

	int p1xBorder;
	int p1yBorder;

	bool dir1;
	bool dir2;
	bool dir3;
	bool dir4;

	bool dir1p2;
	bool dir2p2;
	bool dir3p2;
	bool dir4p2;

	int iright1;
	int idown1;
	int iright2;
	int idown2;

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;

	int p1counter;

	unsigned int top_layer;
	std::vector<MyEntity*> layers;


};

#endif /* SCENE00_H */
