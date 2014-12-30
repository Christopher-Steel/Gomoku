#pragma once

#include "AState.h"
#include "ModuleGame.hpp"


class							GameState : public AState
{
public:
	GameState(Game *game);
	~GameState();

	void						initialize();
	void						stop(void);
	bool						handleKeyEvent(const sf::Event &event);
	bool						handleKeyState();
	void						update();
	
private:
	struct									Player
	{
		sf::Sprite							sprite;
		int									posX;
		int									posY;
	};
	void						updateBackground();
	void						updateHUD();

	unsigned int 				findX(unsigned int pos);
	unsigned int 				findY(unsigned int pos);
	void						averagePosition(Player &p, int *x2, int *y2);
	bool						checkPosition(const Player &p);
	bool									putPion(Player &, bool);



	std::vector<Player>			_player1;
	std::vector<Player>			_player2;
	std::vector<Player>			_ia;
	int							_idBoss;
	unsigned int				_idPlayer[Gomoku::Player::MAX];
	unsigned int				_idHud[Gomoku::HUD::MAX];
	unsigned int				_idBackground[Gomoku::GameBackground::MAX];
	ModuleGame 					*_moduleGame;
	bool						_player;
	std::map<std::string, sf::Sprite*>		_sprite;
	std::map<std::string, sf::Texture*>		_texture;
	sf::FloatRect							_jvsj;
	sf::FloatRect							_jvsia;
};