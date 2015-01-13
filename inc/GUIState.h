#pragma once

#include "AState.h"

class							GUIState : public AState
{
public:
	GUIState(GameAction *_gameAction);
	~GUIState();

	void						initialize();
	bool						handleKeyEvent(const sf::Event &event);

private:

	unsigned int				_state;
	unsigned int				_id[Gomoku::MainMenu::MAX];
};