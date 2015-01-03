#pragma once

#include "AState.h"

class							GUIPauseState : public AState
{
public:
	GUIPauseState(GameAction *_gameAction);
	~GUIPauseState();

	void						initialize();
	void						stop(void);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();

private:

	unsigned int				_state;
	unsigned int				_id[Gomoku::PauseMenu::MAX];
};