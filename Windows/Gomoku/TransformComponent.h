#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

struct													TransformComponent
{
	sf::Vector2f										position;
	sf::Vector2f										scale;
	float												rotation;
	sf::Vector2f										size;
	sf::Vector2f										origin;
	sf::Transform										transform;
};