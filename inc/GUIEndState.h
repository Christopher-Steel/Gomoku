#pragma once

#include "AState.h"

class							GUIEndState : public AState
{
public:

	enum Result
	{
		WHITE,
		BLACK,
		AI,
		MAX
	};

	GUIEndState(GameAction *_gameAction, const Result &result);
	~GUIEndState();

	void						initialize();
	bool						handleKeyEvent(const sf::Event &event);

private:

	std::string					_result;
	unsigned int				_state;
	unsigned int				_id[Gomoku::EndMenu::MAX];
};