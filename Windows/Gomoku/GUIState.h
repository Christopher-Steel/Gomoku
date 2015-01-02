#pragma once

#include "AState.h"

class							GUIState : public AState
{
public:
	GUIState(Game *game);
	~GUIState();

	void						initialize();
	void						stop(void);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();

private:

	unsigned int				_state;
	unsigned int				_id[Gomoku::MainMenu::MAX];
};