/**
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 *
 * @file gamescene.h
 *
 * @brief description of GameScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H



#include <vector>
#include <rt2d/timer.h>
#include <rt2d/scene.h>
#include <rt2d/text.h>
#include "basicentity.h"
#include "player.h"
#include "grid.h"
#include "endmenu.h"
#include "button.h"

/// @brief The GameScene class is the Scene implementation.
class GameScene : public Scene
{

public:
	/// @brief Constructor
	GameScene();
	/// @brief Destructor
	virtual ~GameScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	virtual void endScreen();
	void restart();
protected:

	std::vector<Text*> text;
	std::vector<BasicEntity*> layers;

private:
	Player* player1;
	Player* player2;
	Grid* grid;
	BasicEntity* gridBackground;
	BasicEntity* gameBackground;
	EndMenu* endMenu;
	Button* restartButton;
	/// @brief a Timer to rotate the color every n seconds
	Timer t;

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

	int p1x;
	int p1y;
	int p2x;
	int p2y;

	Point2 p1lastSpritePos;
	Point2 p2lastSpritePos;

	unsigned int top_layer;

};

#endif /* SCENE00_H */
