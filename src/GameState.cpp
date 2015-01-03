
#include <iostream>

#include "GameState.h"


GameState::GameState(GameAction *gameAction, Gomoku::MainMenu::MODE mode) : AState(gameAction), _printer(_goban), _black(nullptr), _white(nullptr)
{
	_isBlocking = true;
}

GameState::~GameState() {}

void						GameState::initialize()
{
	_gameAction->factory.createGameBackground(_idBackground, _world, _gameAction->getScreenSize());
	_gameAction->factory.createHUD(_idHud, _world, _gameAction->getScreenSize());
	// _player = false;
	// _moduleGame = new ModuleGame();
	if (_mode == Gomoku::MainMenu::PLAYERPLAYER) {
		std::function<APlayer *(PlayerColor)>	playerFactory[] =
		{
		  [](PlayerColor c){ return new Human(c); },
		  [](PlayerColor c){ return new Human(c); }
		};
		// APlayer::Move	move;
		// APlayer	*currentPlayer = nullptr;

		_black.reset(playerFactory[static_cast<unsigned>(PlayerType::HUMAN) - 1](PlayerColor::BLACK));
		_white.reset(playerFactory[static_cast<unsigned>(PlayerType::HUMAN) - 1](PlayerColor::WHITE));
	}
	else {
		std::function<APlayer *(PlayerColor)>	playerFactory[] =
		{
		  [](PlayerColor c){ return new Human(c); },
		  [](PlayerColor c){ return new Human(c); } // replace with AI
		};
		_black.reset(playerFactory[static_cast<unsigned>(PlayerType::HUMAN) - 1](PlayerColor::BLACK));
		_white.reset(playerFactory[static_cast<unsigned>(PlayerType::AI) - 1](PlayerColor::WHITE));
	}
	_valueWhite = 0;
	_valueBlack = 0;
  	_currentPlayer = _black.get();
}


void						GameState::addBlackStoneToScore() {
	_gameAction->factory.createGameBlackStone(_world, sf::Vector2f(10,550 + _valueBlack));
	_gameAction->factory.createGameBlackStone(_world, sf::Vector2f(25,550 + _valueBlack));
	_valueBlack += 25;
}


void						GameState::addWhiteStoneToScore() {
	_gameAction->factory.createGameWhiteStone(_world, sf::Vector2f(10,150 + _valueWhite));
	_gameAction->factory.createGameWhiteStone(_world, sf::Vector2f(25,150 + _valueWhite));
	_valueWhite += 25;
}



void					GameState::averagePosition(Stone &p, int *x2, int *y2) {
	int					x;
	int					y;

	p.y < 195 ? p.y = 195 : p.y;
	p.x < 215 ? p.x = 215 : p.x;
	
	y = (p.y - 195) % 35;
	x = (p.x - 215) % 50;
	if (y <= (35 / 2))
		*y2 = p.y - (y % 35);
	else
		*y2 = p.y - (y % 35) + 35;
	if (x < (50 / 2))
		*x2 = p.x - (x % 50);
	else
		*x2 = p.x - (x % 50) + 50;
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
		if (event.mouseButton.button == sf::Mouse::Left) {
			int 				tmpX;
			int 				tmpY;

			Stone					stone;
			stone.x = event.mouseButton.x;
			stone.y = event.mouseButton.y;
			if (stone.x > 1130 || stone.x < 180 || stone.y > 840 || stone.y < 180)
				return true;
			averagePosition(stone, &tmpX, &tmpY);
			stone.x = tmpX;
			stone.y = tmpY;
			if (checkPosition(stone) == true) {
				runModuleGame(stone);
			}
			if (_mode == Gomoku::MainMenu::PLAYERIA) {
				// ludo function's 
				//runModuleGame(stone);
			}
			//supprIndex(_moduleGame->getIndex());
		}
	}
	return (true);
}

void						GameState::supprIndex(const unsigned int *index) {
	deleteStone(index[0]);
	deleteStone(index[1]);
}

void						GameState::stop()
{

}

void					GameState::runModuleGame(Stone &stone) {
  // _printer.print();
	if (not _goban.isGameOver()) {
		// _move = _currentPlayer->getMove();
		// std::cout << "x = " << stone.x << " y = " << stone.y << std::endl;
		if (not _goban.setStone(_currentPlayer->getColor(), Calcul::findX(stone.x - 215), Calcul::findY(stone.y - 195))) {
		  _printer.printIllegalMove();
		  return;
		}
		_currentPlayer = (_currentPlayer == _black.get() ? _white.get() : _black.get());
		putStone(stone, _currentPlayer->getColor());
		_printer.print();
		if (_goban.isGameOver())
		{
			_printer.printVictory(_goban.isGameOver());
			detectEnd(_goban.isGameOver());			
		}
		return;
	}

	_printer.printVictory(_goban.isGameOver());
	detectEnd(_goban.isGameOver());
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
	
	stone.x = Calcul::findX(p.x - 215);
	stone.y = Calcul::findY(p.y - 195);
	if (player == PlayerColor::BLACK)
	{
		 if (checkPosition(stone) != false) {
			stone.color = true;
			stone.id = _gameAction->factory.createGameWhiteStone(_world, sf::Vector2f(p.x - 21, p.y - 21));
		 	_player1.push_back(stone);
		 	return (true);
		 }
		return (false);
	}
	else if (player == PlayerColor::WHITE)
	{
		 if (checkPosition(stone) != false) {
			stone.color = false;
			stone.id = _gameAction->factory.createGameBlackStone(_world, sf::Vector2f(p.x - 21,p.y - 21));
		 	_player2.push_back(stone);
		 	return (true);
		 }
		return (false);
	}
	return (true);
}

GameState::Stone 					&GameState::findStone(unsigned int rank) {
	unsigned int tmp = rank;
        int y = -1;
	unsigned int x = rank % 18;

	bool	findx = false;
	bool	findy = false;
	Stone s;

	while (tmp > 0) {
		y++;
		tmp /= 18;	
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
	for (std::vector<Stone>::iterator it = _player2.begin(); it != _player2.end(); ++it) {
		if (it->x == x) {
			findx = true;
			if (it->y == y)
				findy = true;
			if (findx == true && findy == true) {
				return (*it);
			}
		}
	}
	return (s);
}



void 					GameState::deleteStone(unsigned int rank) {
	int tmp = rank;
        int y = -1;
	unsigned int x = rank % 18;

	bool	findx = false;
	bool	findy = false;
	bool	find = false;
	int 	rankId = 0;

	while (tmp > 0) {
		y++;
		tmp /= 18;	
	}
	tmp = -1;
	std::cout << "x = " << x << "y = " << y << std::endl;
	for (std::vector<Stone>::iterator it = _player1.begin(); it != _player1.end(); ++it) {
		++tmp;
		if (it->x == x) {
			findx = true;
			if (it->y == y)
				findy = true;
			if (findx == true && findy == true) {
				find = true;
				break;
			}
		}
	}
	if (find == true) {
		if ((rankId = findStone(rank).id) != 0)
			_world.renderComponents[rankId] = NULL;
		_player1.erase(_player1.begin() + tmp);
		return;
	}
	find = false;
	tmp = -1;
	for (std::vector<Stone>::iterator it = _player2.begin(); it != _player2.end(); ++it) {
		++tmp;
		if (it->x == x) {
			findx = true;
			if (it->y == y)
				findy = true;
			if (findx == true && findy == true) {
				find = true;
			}
		}
	}
	if (find == true) {
		if ((rankId = findStone(rank).id) != 0)
			_world.renderComponents[rankId] = NULL;
		_player2.erase(_player2.begin() + tmp);
	}

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
bool						GameState::handleKeyState()
{

	// sf::Vector2f			direction = sf::Vector2f(0.0f, 0.0f);
	// sf::Vector2f			size = _world.transformComponents[_idPlayer[Gomoku::Player::SHIP]]->size;
	// sf::Vector2f			scale = _world.transformComponents[_idPlayer[Gomoku::Player::SHIP]]->scale;
	// sf::Vector2f			pos = _world.transformComponents[_idPlayer[Gomoku::Player::SHIP]]->position;

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pos.y > 0)
	// 	direction += sf::Vector2f(0, -1);

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pos.y < _gameAction->getScreenSize().y - (size.y * scale.y))
	// 	direction += sf::Vector2f(0, 1);

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0)
	// 	direction += sf::Vector2f(-1, 0);

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x < _gameAction->getScreenSize().x - (size.x * scale.x))
	// 	direction += sf::Vector2f(1, 0);

	// _world.movementComponents[_idPlayer[RType::Player::SHIP]]->direction = direction;
	// static int nb = 0;
	// if (nb == 0)
	// 	_rfc->sendMove(_world.transformComponents[_idPlayer[RType::Player::SHIP]]->position, direction);
	// ++nb;
	// if (nb > 50)
	// 	nb = 0;

	// // pan pan
	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	// 	_world.weaponComponents[_idPlayer[Gomoku::Player::WEAPON_1]]->fire = true;

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	// 	_world.weaponComponents[_idPlayer[Gomoku::Player::WEAPON_2]]->fire = true;

	return (true);
}

void						GameState::update()
{
	// TimerSystem::update(_world, elapsed);
	// WeaponSystem::update(_world, elapsed, _gameAction->factory, _gameAction->getScreenSize());
	// ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, _gameAction->getScreenSize());
	// CollisionSystem::update(_world, sf::Vector2u(10, 10), _gameAction->getScreenSize());
	// HealthSystem::update(_world, elapsed, _gameAction->factory);
	// AnimationSystem::update(_world, elapsed);
	// DeathSystem::update(_world);
	// this->updateBackground();
	// this->updateHUD();

	// Si vous voulez savoir ce que ça fait, commentez le et essayez d'appuyer sur echap et de bouger en meme temps ingameAction
	// _world.movementComponents[_idPlayer[RType::Player::SHIP]]->direction = sf::Vector2f(0.0f, 0.0f);
}


void						GameState::updateBackground()
{
	// if (_world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->position.x + _world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->size.x <= 0.0f)
	// 	_world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->position.x = _world.transformComponents[_idBackground[RType::GameBackground::DEFAULT]]->size.x;

	// if (_world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->position.x + _world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->size.x <= 0.0f)
	// 	_world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->position.x = _world.transformComponents[_idBackground[RType::GameBackground::REVERSED]]->size.x;
}

void						GameState::updateHUD()
{
	// InfoComponent			*info = _world.infoComponents[_idPlayer[RType::Player::SHIP]];
	// sf::Vector2f			size = sf::Vector2f(200, 10);
	// float					ratio;
	
	// _world.textComponents[_idHud[Gomoku::GAME::SCORE]]->string = "Stone : ";

	// ratio = (static_cast<float>(info->life) / static_cast<float>(info->maxLife));
	// _world.transformComponents[_idHud[RType::HUD::LIFEBAR]]->size = size * ratio;

	// ratio = (static_cast<float>(info->shield) / static_cast<float>(info->maxShield));
	// _world.transformComponents[_idHud[RType::HUD::SHIELDBAR]]->size = size * ratio;
}
