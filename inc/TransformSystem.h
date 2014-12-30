#pragma once

#include "World.h"

class							TransformSystem
{
public:
	static void					update(World &world, const sf::Vector2u &screenSize);
private:
	TransformSystem();
	TransformSystem(const TransformSystem &rhs);
	TransformSystem &operator=(const TransformSystem &rhs);

	// static void					applyScroll(const unsigned int id, World &world, const sf::Time &elapsed);
	// static bool					applyMovement(const unsigned int id, World &world, const sf::Time &elapsed, const sf::Vector2u &screenSize);
	// static void					applySpin(const unsigned int id, World &world, const sf::Time &elapsed);
	// static void					applyGrow(const unsigned int id, World &world, const sf::Time &elapsed);

	// static void					updateChildren(const unsigned int id, World &world, const sf::Vector2f &movement);
	// static void					updateChildren(const unsigned int id, World &world, const float spinValue);

	static void					computeTransform(const unsigned int id, World &world);
};