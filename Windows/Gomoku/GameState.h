#pragma once

#include "AState.h"
#include "ModuleGame.hpp"
#include "GameState.h"
#include "GUIPauseState.h"
#include "GUIEndState.h"
#include "PlayerInfo.hpp"

#include "Calcul.h"


class							GameState : public AState
{
public:
	GameState(Game *game, Gomoku::MainMenu::MODE);
	~GameState();

	void						initialize();
	void						stop();
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();
	void						update();
	
private:
	struct									Stone
	{
		bool								color = false; // false == noir true == black
		unsigned int						x;
		unsigned int						y;
		unsigned int 						id;
	};

	void						updateBackground();
	void						updateHUD();

	// unsigned int 				findX(unsigned int pos);
	// unsigned int 				findY(unsigned int pos);
	Stone  						&findStone(unsigned rank);
	void 						deleteStone(unsigned rank);
	void						averagePosition(Stone &p, int *x2, int *y2);
	bool						checkPosition(const Stone &p);
	bool						putStone(Stone &, bool);
	bool						eatStone(Stone &, bool);
	void						detectEnd();
	void						runModuleGame(Stone &);



	std::vector<Stone>			_player1;
	std::vector<Stone>			_player2;
	std::vector<Stone>			_ia;

	unsigned int				_idPlayer[Gomoku::Player::MAX];
	unsigned int				_idHud[Gomoku::HUD::MAX];
	unsigned int				_idBackground[Gomoku::GameBackground::MAX];
	ModuleGame 					*_moduleGame;
	bool						_player;

	Gomoku::MainMenu::MODE					_mode;
	PlayerColor								_plcl = PlayerColor::NONE;
	PlayerColor								_plclTmp = PlayerColor::NONE;

};