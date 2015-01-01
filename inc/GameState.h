#pragma once

#include "AState.h"
#include "ModuleGame.hpp"
#include <list>


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
		int									x;
		int									y;
		unsigned int 						id;
	};
	void						updateBackground();
	void						updateHUD();

	unsigned int 				findX(unsigned int pos);
	unsigned int 				findY(unsigned int pos);
	void						averagePosition(Stone &p, int *x2, int *y2);
	bool						checkPosition(const Stone &p);
	bool						putPion(Stone &, bool);



	std::vector<Stone>			_player1;
	std::vector<Stone>			_player2;
	std::vector<Stone>			_ia;

	unsigned int				_idPlayer[Gomoku::Player::MAX];
	unsigned int				_idHud[Gomoku::HUD::MAX];
	unsigned int				_idBackground[Gomoku::GameBackground::MAX];
	ModuleGame 					*_moduleGame;
	bool						_player;
	// std::list<Stone>			_stone;
	std::map<std::string, sf::Sprite*>		_sprite;
	// std::map<std::string, sf::Texture*>		_texture;
	// sf::FloatRect							_jvsj;
	// sf::FloatRect							_jvsia;
	// int 						*_allStone;
	Gomoku::MainMenu::MODE					_mode;
	PlayerColor								plcl = PlayerColor::NONE;
	PlayerColor								plclTmp = PlayerColor::NONE;

};