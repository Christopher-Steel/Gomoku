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

	GUIEndState(Game *game, const Result &result);
	~GUIEndState();

	void						initialize();
	void						stop(void);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();

private:

	std::string					_result;
	unsigned int				_state;
	unsigned int				_id[Gomoku::EndMenu::MAX];
};