#pragma once

#include "AState.h"

class							GUIPauseState : public AState
{
public:
	GUIPauseState(GameAction *_gameAction);
	~GUIPauseState();

	void						initialize();
	bool						handleKeyEvent(const sf::Event &event);

private:

	unsigned int				_state;
	unsigned int				_id[Gomoku::PauseMenu::MAX];
};