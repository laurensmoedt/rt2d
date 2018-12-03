/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file player.h
 *
 * @brief description of MyEntity behavior.
 */


#ifndef PLAYER_H
#define PLAYER_H

#include <rt2d/entity.h>

class Player : public Entity
{
public:

	Player();

	virtual ~Player();

	virtual void update(float deltaTime);

private:
	/* add your private declarations */

};

#endif /* PLAYER_H */
