#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>

struct															RenderComponent
{
	enum Plane
	{
		HUD = 0,
		FX = 1,
		DEFAULT = 2,
		PARTICLE = 3,
		SEMI_FAR = 15,
		BACKGROUND = 30
	};

	const sf::Texture											*texture;
	sf::VertexArray												vertices;
	unsigned int												plane;
	sf::Color													color;
	sf::Transform												transform;
};