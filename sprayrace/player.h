/**
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 *
 * @file player.h
 *
 * @brief description of BasicEntity behavior.
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

};

#endif /* PLAYER_H */
