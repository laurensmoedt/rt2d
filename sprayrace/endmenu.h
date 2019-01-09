/**
* Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
*
* @file menu.h
*
* @brief description of menu behavior.
*/

#ifndef ENDMENU_H
#define ENDMENU_H


#include <rt2d/entity.h>


class EndMenu : public Entity
{


public:

	EndMenu();

	virtual ~EndMenu();


	virtual void update(float deltaTime);

private:

};

#endif /* MYENTITY_H */
