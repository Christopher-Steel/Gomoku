#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>

#include "World.h"

class								RenderSystem
{
public:
	static void						update(sf::RenderWindow *window, World &world);
private:
	RenderSystem();
	RenderSystem(const RenderSystem &rhs);
	RenderSystem &operator=(const RenderSystem &rhs);

	static void						draw(sf::RenderWindow *window, const std::vector<RenderComponent *> &components);
	static bool						sortFunction(const RenderComponent *a, const RenderComponent *b);
};