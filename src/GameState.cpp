#include "GameState.h"
#include "GUIPauseState.h"
#include "GUIEndState.h"
//#include "RFCClient.h"

GameState::GameState(Game *game) : AState(game)
{
	//game->_rfc = &_rfc;
	_isBlocking = true;
}

GameState::~GameState() {}

void						GameState::initialize()
{
	//unsigned int			id[1];

	// _client = Network::Client::connect<Network::udp::ip4>(Network::Client::Config("127.0.0.1", 6325), ::hpl::bind(&GameState::onConnectEvent, this, ::hpl::Placeholder::_1));
	_game->factory.createGameBackground(_idBackground, _world, _game->getScreenSize());
	_game->factory.createHUD(_idHud, _world, _game->getScreenSize());
	_game->factory.createPlayer(_idPlayer, _world);
	//_game->factory.createTestEnemy(id, _world);
}

void						GameState::stop(void)
{
	// _client->socket.close();
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
		_game->pushState(new GUIEndState(_game, GUIEndState::LOSE));
		return (true);
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
	this->updateBackground();
	this->updateHUD();

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
	
	// _world.textComponents[_idHud[RType::HUD::SCORE]]->string = "Score : " + std::to_string(info->score);

	// ratio = (static_cast<float>(info->life) / static_cast<float>(info->maxLife));
	// _world.transformComponents[_idHud[RType::HUD::LIFEBAR]]->size = size * ratio;

	// ratio = (static_cast<float>(info->shield) / static_cast<float>(info->maxShield));
	// _world.transformComponents[_idHud[RType::HUD::SHIELDBAR]]->size = size * ratio;
}
