#pragma once

#include "AState.h"

#include <functional>
# include <memory>

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

class							GameState : public AState
{
public:
	GameState(GameAction *_gameAction, Gomoku::MainMenu::MODE);
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
	        int						y;
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
	bool						putStone(Stone &, const PlayerColor &);
	bool						eatStone(Stone &, bool);
	void						detectEnd(const PlayerColor &);
	void						runModuleGame(Stone &);
	void						addBlackStoneToScore();
	void						addWhiteStoneToScore();
	void						supprIndex(const unsigned int *);


	std::vector<Stone>			_player1;
	std::vector<Stone>			_player2;
	std::vector<Stone>			_ia;

	unsigned int				_idPlayer[Gomoku::Player::MAX];
	unsigned int				_idHud[Gomoku::HUD::MAX];
	unsigned int				_idBackground[Gomoku::GameBackground::MAX];
	// ModuleGame 					*_moduleGame;
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


};
