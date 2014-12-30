#pragma once

#include "AState.h"

class							GameState : public AState
{
public:
	GameState(Game *game);
	~GameState();

	void						initialize();
	void						stop(void);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();
	void						update(const sf::Time &elapsed);
	
private:
	void						updateBackground();
	void						updateHUD();

	int							_idBoss;
	unsigned int				_idPlayer[Gomoku::Player::MAX];
	unsigned int				_idHud[Gomoku::HUD::MAX];
	unsigned int				_idBackground[Gomoku::GameBackground::MAX];
};