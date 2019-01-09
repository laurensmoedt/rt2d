/**
 * Copyright 2018 Laurens Moedt <laurensmoedt@gmail.com>
 *
 * @file basicentity.h
 *
 * @brief description of BasicEntity behavior.
 */

#ifndef MYENTITY_H
#define MYENTITY_H

#include <rt2d/entity.h>

/// @brief The BasicEntity class is the Entity implementation.
class BasicEntity : public Entity
{



public:
	/// @brief Constructor
	BasicEntity();
	/// @brief Destructor
	virtual ~BasicEntity();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
