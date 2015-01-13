
#include <iostream>

#include "GameState.h"

GameState::GameState(GameAction *gameAction, Gomoku::MainMenu::MODE mode) : AState(gameAction), _printer(_goban), _black(nullptr), _white(nullptr)
{
	_mode = mode;
	_isBlocking = true;
}

GameState::~GameState() {}

void						GameState::initialize()
{
	_gameAction->factory.createGameBackground(_idBackground, _world, _gameAction->getScreenSize());
	_gameAction->factory.createHUD(_idHud, _world, _gameAction->getScreenSize());
	if (_mode == Gomoku::MainMenu::PLAYERPLAYER) {
		std::function<APlayer *(PlayerColor)>	playerFactory[] =
		{
		  [](PlayerColor c){ return new Human(c); },
		  [](PlayerColor c){ return new Human(c); }
		};
		_black.reset(playerFactory[static_cast<unsigned>(PlayerType::HUMAN) - 1](PlayerColor::BLACK));
		_white.reset(playerFactory[static_cast<unsigned>(PlayerType::HUMAN) - 1](PlayerColor::WHITE));
	}
	else {
		std::function<APlayer *(PlayerColor)>	playerFactory[] =
		{
		  [](PlayerColor c){ return new Human(c); },
		  [](PlayerColor c){ return new AI(c); }
		};
		_black.reset(playerFactory[static_cast<unsigned>(PlayerType::HUMAN) - 1](PlayerColor::BLACK));
		_white.reset(playerFactory[static_cast<unsigned>(PlayerType::AI) - 1](PlayerColor::WHITE));
	}
	_valueWhite = 0;
	_valueBlack = 0;
  	_currentPlayer = _black.get();
	while (_gameAction->factory.changeCurrentPlayer(_world) != false);
}


void						GameState::addBlackStoneToScore() {
	_gameAction->factory.createGameBlackStone(_world, sf::Vector2f(10,550 + _valueBlack));
	_gameAction->factory.createGameBlackStone(_world, sf::Vector2f(40,550 + _valueBlack));
	_valueBlack += 50;
}


void						GameState::addWhiteStoneToScore() {
	_gameAction->factory.createGameWhiteStone(_world, sf::Vector2f(10,150 + _valueWhite));
	_gameAction->factory.createGameWhiteStone(_world, sf::Vector2f(40,150 + _valueWhite));
	_valueWhite += 50;
}



void					GameState::averagePosition(Stone &p, int *x2, int *y2) {
	int					x;
	int					y;

	p.y < AXEY ? p.y = AXEY : p.y;
	p.x < AXEX ? p.x = AXEX : p.x;
	
	y = (p.y - AXEY) % SPACE;
	x = (p.x - AXEX) % SPACE;
	if (y <= (SPACE / 2))
		*y2 = p.y - (y % SPACE);
	else
		*y2 = p.y - (y % SPACE) + SPACE;
	if (x < (SPACE / 2))
		*x2 = p.x - (x % SPACE);
	else
		*x2 = p.x - (x % SPACE) + SPACE;
	p.x = *x2;
	p.y = *y2;
}

bool						GameState::handleKeyEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		_gameAction->pushState(new GUIPauseState(_gameAction));
		return (true);
	}

	// simuler une fin de partie
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
		_gameAction->pushState(new GUIEndState(_gameAction, GUIEndState::BLACK));
		return (true);
	}
	
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V) {
		deleteStone(0);
		return (true);
	}

	if (event.type == sf::Event::MouseButtonReleased) {
			int 				tmpX;
			int 				tmpY;

			Stone					stone;
		if (event.mouseButton.button == sf::Mouse::Left) {
			stone.x = event.mouseButton.x;
			stone.y = event.mouseButton.y;
			if (stone.x > 1100 || stone.x < 240 || stone.y > 980 || stone.y < 110)
				return true;
			averagePosition(stone, &tmpX, &tmpY);
			stone.x = tmpX;
			stone.y = tmpY;
			if (checkPosition(stone) == true) {
				runModuleGame(stone);
			}
			if (_mode == Gomoku::MainMenu::PLAYERIA) {
			  APlayer::Move			move;
			  _currentPlayer->chooseMove(_goban);
			  move = _currentPlayer->getMove();
			  stone.x = move.x * SPACE + AXEX;
			  stone.y = move.y * SPACE + AXEY;
			  runModuleGame(stone);
			}
		}
	}
	return (true);
}

void						GameState::supprIndex(std::list<unsigned int> &list) {
	unsigned	i = 0;
	PlayerColor	tmp = PlayerColor::NONE;

	for (std::list<unsigned int>::const_iterator it = list.begin(); it != list.end(); ++it) {
		tmp = deleteStone(*it);
		++i;
	}
	i /= 2;
	while (i > 0)
	  {
	    if (tmp == PlayerColor::WHITE)
	      addWhiteStoneToScore();
	    else if (tmp == PlayerColor::BLACK)
	      addBlackStoneToScore();
	    --i;
	  }
	list.clear();
}

void					GameState::runModuleGame(Stone &stone) {
	if (not _goban.isGameOver()) {
		if (not _goban.setStone(_currentPlayer->getColor(), Calcul::findX(stone.x - AXEX), Calcul::findY(stone.y - AXEY))) {
		  _printer.printIllegalMove();
		  return;
		}
		putStone(stone, _currentPlayer->getColor());
		_currentPlayer = (_currentPlayer == _black.get() ? _white.get() : _black.get());
		_gameAction->factory.changeCurrentPlayer(_world);
		_printer.print();
		supprIndex(_goban.getCapture());
		if (_goban.isGameOver())
		{
			_printer.printVictory(_goban.isGameOver());
			if (_end == true) {
				detectEnd(_goban.isGameOver());
				_end = false;
			}
			return;
		}
		return;
	}
	_printer.printVictory(_goban.isGameOver());
	if (_end == true) {
		detectEnd(_goban.isGameOver());
		_end = false;
	}
}

void					GameState::detectEnd(const PlayerColor &player) {
	if (player == 0)
		_gameAction->pushState(new GUIEndState(_gameAction, GUIEndState::AI));
	else if (player == 1)
		_gameAction->pushState(new GUIEndState(_gameAction, GUIEndState::WHITE));
	else if (player == 2)
		_gameAction->pushState(new GUIEndState(_gameAction, GUIEndState::BLACK));
}

bool					GameState::putStone(Stone &p, const PlayerColor &player)
{
	Stone stone;
	
	stone.x = Calcul::findX(p.x - AXEX);
	stone.y = Calcul::findY(p.y - AXEY);
	if (player == PlayerColor::BLACK)
	{
		 if (checkPosition(stone) != false) {
			stone.color = true;
			stone.id = _gameAction->factory.createGameBlackStone(_world, sf::Vector2f(p.x - 21,p.y - 21));
		 	_player1.push_back(stone);
		 	return (true);
		 }
		return (false);
	}
	else if (player == PlayerColor::WHITE)
	{
		 if (checkPosition(stone) != false) {
			stone.color = false;
			stone.id = _gameAction->factory.createGameWhiteStone(_world, sf::Vector2f(p.x - 21, p.y - 21));
		 	_player2.push_back(stone);
		 	return (true);
		 }
		return (false);
	}
	return (true);
}

GameState::Stone 					&GameState::findStone(unsigned int rank) {
	int tmp = rank;
    int y = -1;
	unsigned int x = rank % 19;

	bool	findx = false;
	bool	findy = false;
	while (tmp > 0) {
		++y;
		tmp -= 19;	
	}
	for (std::vector<Stone>::iterator it = _player1.begin(); it != _player1.end(); ++it) {
		if (it->x == x) {
			findx = true;
			if (it->y == y)
				findy = true;
			if (findx == true && findy == true) {
				return (*it);
			}
		}
	}
	std::vector<Stone>::iterator it;
	for (it = _player2.begin(); it != _player2.end(); ++it) {
		if (it->x == x) {
			findx = true;
			if (it->y == y)
				findy = true;
			if (findx == true && findy == true) {
				return (*it);
			}
		}
	}
	return (*it);
}



PlayerColor 					GameState::deleteStone(unsigned int rank) {
	bool	find = false;
	int tmp = -1;
	unsigned int 	rankId = 0;
	if ((rankId = findStone(rank).id) != 0) {
		_world.renderComponents[rankId] = NULL;
		for (std::vector<Stone>::iterator it = _player1.begin(); it != _player1.end(); ++it) {
			++tmp;
			if (it->id == rankId) {
				find = true;
				break;
			}
		}
		if (find == true) {
			_player1.erase(_player1.begin() + tmp);
			return PlayerColor::BLACK;
		}
		tmp = -1;
		for (std::vector<Stone>::iterator it = _player2.begin(); it != _player2.end(); ++it) {
			++tmp;
			if (it->id == rankId) {
					find = true;
					break;
			}
		}
		if (find == true) {
			_player2.erase(_player2.begin() + tmp);
			return PlayerColor::WHITE;
		}
	}
	return PlayerColor::NONE;
}

bool					GameState::checkPosition(const Stone &stone) {
	bool	x = false;
	bool	y = false;

	for (std::vector<Stone>::iterator it = _player1.begin(); it != _player1.end(); ++it) {
		if (it->x == stone.x) {
			x = true;
			if (it->y == stone.y)
				y = true;
			if (x == true && y == true)
				return (false);
		}
	}
	for (std::vector<Stone>::iterator it = _player2.begin(); it != _player2.end(); ++it) {
		if (it->x == stone.x) {
			x = true;
			if (it->y == stone.y)
				y = true;
			if (x == true && y == true)
				return (false);
		}
	}
	return (true);
}


void						GameState::update()
{
	TransformSystem::update(_world, _gameAction->getScreenSize());
}