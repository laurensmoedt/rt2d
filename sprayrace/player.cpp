/**
 * This class describes BasicEntity behavior.
 *
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 */

 #include "player.h"

Player::Player(RGBAColor c)
{

	this->addSprite("assets/playerR.tga");
	this->scale = Point3(1.5f, 1.5f, 1.5f);
	this->sprite()->color = c;

	
};

Player::~Player()
{

}


void Player::update(float deltaTime)
{
	
}
