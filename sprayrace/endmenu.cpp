/**
* This class describes BasicEntity behavior.
*
* Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
*/

#include "endmenu.h"

EndMenu::EndMenu() : Entity()
{
	this->addSprite("assets/endMenu.tga");
	this->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	
}

EndMenu::~EndMenu()
{

}

void EndMenu::update(float deltaTime)
{

}
