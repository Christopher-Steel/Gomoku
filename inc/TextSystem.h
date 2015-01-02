#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "World.h"

class						TextSystem
{
public:
	static void				update(sf::RenderWindow *window, World &world);
private:
	TextSystem();
	TextSystem(const TextSystem &rhs);
	TextSystem &operator=(const TextSystem &rhs);
};