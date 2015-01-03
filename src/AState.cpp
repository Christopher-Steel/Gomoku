#include "AState.h"

AState::AState(GameAction *gameAction) : _gameAction(gameAction)
{
}

AState::~AState()
{
}

void							AState::update()
{
	//TimerSystem::update(_world, elapsed);
	TransformSystem::update(_world, _gameAction->getScreenSize());
}

void							AState::draw(sf::RenderWindow *window)
{
	RenderSystem::update(window, _world);
	TextSystem::update(window, _world);
}

bool							AState::isBlocking() const
{
	return (_isBlocking);
}