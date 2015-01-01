#include "GameState.h"
#include "GUIPauseState.h"
#include "GUIEndState.h"
#include "PlayerInfo.hpp"
#include <iostream>

GameState::GameState(Game *game, Gomoku::MainMenu::MODE mode) : AState(game)
{
	_isBlocking = true;
	_player = false;
	_mode = mode;
}

GameState::~GameState() {}

void					GameState::averagePosition(Stone &p, int *x2, int *y2) {
	int					x;
	int					y;

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

unsigned int 	GameState::findX(unsigned int pos) {
	unsigned int tmp = pos;
	unsigned int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 50;	
	}
	return (ret);
}

unsigned int 	GameState::findY(unsigned int pos) {
	unsigned int tmp = pos;
	unsigned int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 35;
	}
	return (ret);
}

void						GameState::initialize()
{
	_game->factory.createGameBackground(_idBackground, _world, _game->getScreenSize());
	_game->factory.createHUD(_idHud, _world, _game->getScreenSize());
	// _game->factory.createGameBlackStone(_world, sf::Vector2f(10,10));
	_player = false;
	_moduleGame = new ModuleGame();
	if (_mode == Gomoku::MainMenu::PLAYERPLAYER)
		_moduleGame->initPlayer(PlayerType::HUMAN,PlayerType::HUMAN);
	else
		_moduleGame->initPlayer(PlayerType::HUMAN,PlayerType::AI);


	// sf::Texture tata;
	// unsigned int tmp = _world.createEmptyEntity();
	// 	_world.addRenderComponent(tmp, ComponentFactory::createRenderComponent(_game->_resourceManager.getTexture("ressources/black.png"), RenderComponent::Plane::DEFAULT));
	// 	_world.addTransformComponent(tmp, ComponentFactory::createTransformComponent(sf::Vector2f(120,150), sf::Vector2f(120, 120)));

}

bool						GameState::handleKeyEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		_game->pushState(new GUIPauseState(_game));
		return (true);
	}

	// simuler une fin de partie
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
		_game->pushState(new GUIEndState(_game, GUIEndState::BLACK));
	return (true);
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			Stone				p;
			int 				tmpX;
			int 				tmpY;

			p.x = event.mouseButton.x;
			p.y = event.mouseButton.y;
			averagePosition(p, &tmpX, &tmpY);
			if (checkPosition(p) == true) {
				if ((plcl = _moduleGame->run(findX(p.x - 215), findY(p.y - 195), _player)) == PlayerColor::END) {
					if (plclTmp == PlayerColor::WHITE)
						_game->pushState(new GUIEndState(_game, GUIEndState::WHITE));
					else if (plclTmp == PlayerColor::BLACK)
						_game->pushState(new GUIEndState(_game, GUIEndState::BLACK));
					else
						_game->pushState(new GUIEndState(_game, GUIEndState::AI));
				} else if (plcl == PlayerColor::ERROR) {
				} else {
					plclTmp = plcl;
					putPion(p, _player);
					_player = !_player;
				}
			}
			else {
				// _player = _player;
			}
		}
	}
	return (true);
}


void						GameState::stop()
{

}

bool					GameState::putPion(Stone &p, bool player)
{
	int					x;
	int					y;

	Stone stone;
	stone.x = p.x;
	stone.y = p.y;
	averagePosition(p, &x, &y);
	if (player)
	{
		 std::cout << "white" << std::endl;
		 if (checkPosition(stone) != false) {
			stone.color = true;
			stone.id = _game->factory.createGameWhiteStone(_world, sf::Vector2f(x - 21,y - 21));
		 	_player1.push_back(stone);
		 	return (true);
		 }
		return (false);
	}
	else
	{
		 std::cout << "black" << std::endl;
		 if (checkPosition(stone) != false) {
			stone.color = false;
			stone.id = _game->factory.createGameBlackStone(_world, sf::Vector2f(x - 21,y - 21));
		 	_player2.push_back(stone);
		 	return (true);
		 }
		return (false);
	}
	return (true);
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

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pos.y < _game->getScreenSize().y - (size.y * scale.y))
	// 	direction += sf::Vector2f(0, 1);

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0)
	// 	direction += sf::Vector2f(-1, 0);

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x < _game->getScreenSize().x - (size.x * scale.x))
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
	// WeaponSystem::update(_world, elapsed, _game->factory, _game->getScreenSize());
	// ParticleSystem::update(_world, elapsed);
	TransformSystem::update(_world, _game->getScreenSize());
	// CollisionSystem::update(_world, sf::Vector2u(10, 10), _game->getScreenSize());
	// HealthSystem::update(_world, elapsed, _game->factory);
	// AnimationSystem::update(_world, elapsed);
	// DeathSystem::update(_world);
	// this->updateBackground();
	// this->updateHUD();

	// Si vous voulez savoir ce que ça fait, commentez le et essayez d'appuyer sur echap et de bouger en meme temps ingame
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
