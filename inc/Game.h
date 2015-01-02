#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceManager.h"
#include "GameSpecificFactory.h"
#include "GameEnums.h"

class							AState;

class							Game
{
public:
	Game();
	~Game();

	bool						initialize(const sf::Vector2u &size, const std::string &title);
	void						run();
	void						exit();
	void						pushState(AState *state);
	void						popState();
	sf::Vector2u				getScreenSize() const;

	GameSpecificFactory			factory;

private:
	Game(const Game &rhs);
	Game &operator=(const Game &rhs);

	bool						loadTextures();
	bool						loadFonts();

	ResourceManager				_resourceManager;
	sf::RenderWindow			*_window;
	std::vector<AState *>		_states;
};