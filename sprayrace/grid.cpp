/**
 * This class describes Grid behavior.
 *
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 */

#include "grid.h"

Grid::Grid() : Entity()
{

	gridwidth = 64;
	gridheight = 32;
	cellwidth = 16;
	cellheight = 16;

	// create grid
	this->addGrid("assets/gridBlock.tga", 1, 1, gridwidth, gridheight, cellwidth, cellheight);

	std::vector<Sprite*> spritebatch = this->spritebatch();
	for (size_t i = 0; i < spritebatch.size(); i++)
	{
		spritebatch[i]->color = BLACK;
	}

	this->position = Point2(SWIDTH / 9.4, SHEIGHT / 6.4);
}

Grid::~Grid()
{

}

void Grid::update(float deltaTime)
{


}
