#pragma once

#include <iostream>

#include <string>
#include <map>
#include <vector>

#include "SFML/Graphics.hpp"
#include "ModuleGame.hpp"

class										Graphic
{
public:
	Graphic(sf::RenderWindow &);
	~Graphic();

	PlayerColor								run();
	void									clear();
	void									drawMenuStart();

private:

	struct									Player
	{
		sf::Sprite							sprite;
		int									posX;
		int									posY;
	};
	unsigned int 							findX(unsigned int pos);
	unsigned int 							findY(unsigned int pos);
	void									draw();
	void									drawMenu();
	void									loadTexture();
	bool									putPion(Player &, bool);
	bool									checkPosition(const Player &);
	void									averagePosition(Player &, int *, int *);

	sf::RenderWindow						&_window;
	std::map<std::string, sf::Sprite*>		_sprite;
	std::map<std::string, sf::Texture*>		_texture;
	sf::FloatRect							_jvsj;
	sf::FloatRect							_jvsia;
	std::vector<Player>						_player1;
	std::vector<Player>						_player2;

	ModuleGame								*_game;
};