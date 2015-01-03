#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "World.h"
#include "Systems.h"
#include "GameAction.h"
#include "GameEnums.h"

class							AState
{
public:
	AState(GameAction *gameAction);
	~AState();

	virtual void				initialize() = 0;
	virtual void				stop(void) = 0;
	virtual void				update();
	virtual void				draw(sf::RenderWindow *window);
	virtual bool				handleKeyEvent(const sf::Event &event) = 0;
	virtual bool				handleKeyState() = 0;
	virtual bool				isBlocking() const;
protected:
	bool						_isBlocking;
	World						_world;
	GameAction					*_gameAction;
};