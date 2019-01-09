/**
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 *
 * @file grid.h
 *
 * @brief description of grid behavior.
 */

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <rt2d/entity.h>


class Grid : public Entity
{



public:

	Grid();

	virtual ~Grid();


	virtual void update(float deltaTime);


	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;

private:




};

#endif /* grid_H */
