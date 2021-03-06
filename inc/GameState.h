#pragma once

#include "AState.h"

#include <functional>
#include <memory>
#include <list>
// #include "ModuleGame.hpp"
#include "GameState.h"
#include "GUIPauseState.h"
#include "GUIEndState.h"
#include "PlayerInfo.hpp"

#include "Calcul.h"

#include "GameEnums.h"
#include "Goban.hpp"
#include "GobanPrinter.hpp"
#include "APlayer.hpp"
#include "Human.hpp"
#include "AI.hpp"

#define AXEX 250
#define AXEY 125
#define SPACE 47

class							GameState : public AState
{
public:
	GameState(GameAction *_gameAction, Gomoku::MainMenu::MODE);
	~GameState();

	void						initialize();
	bool						handleKeyEvent(const sf::Event &event);
	void						update();
	
private:
	struct									Stone
	{
		bool								color = false; // false == noir true == black
		unsigned int						x;
	        int						y;
		unsigned int 						id;
	};

	Stone  						&findStone(unsigned rank);
	PlayerColor					deleteStone(unsigned rank);
	void						averagePosition(Stone &p, int *x2, int *y2);
	bool						checkPosition(const Stone &p);
	bool						putStone(Stone &, const PlayerColor &);
	bool						eatStone(Stone &, bool);
	void						detectEnd(const PlayerColor &);
	void						runModuleGame(Stone &);
	void						addBlackStoneToScore();
	void						addWhiteStoneToScore();
	void						supprIndex(std::list<unsigned int> &);


	std::vector<Stone>			_player1;
	std::vector<Stone>			_player2;

	unsigned int				_idPlayer[Gomoku::Player::MAX];
	unsigned int				_idHud[Gomoku::HUD::MAX];
	unsigned int				_idBackground[Gomoku::GameBackground::MAX];
	bool						_player;
	Gomoku::MainMenu::MODE					_mode;
	unsigned int 							_valueWhite;
	unsigned int 							_valueBlack;
	PlayerColor								_plcl = PlayerColor::NONE;
	PlayerColor								_plclTmp = PlayerColor::NONE;

	Goban 						_goban;
	GobanPrinter				_printer;
	std::unique_ptr<APlayer>	_black;
  	std::unique_ptr<APlayer>	_white;

	APlayer::Move	_move;
	APlayer	*_currentPlayer = nullptr;

	bool						_end = true;
};
