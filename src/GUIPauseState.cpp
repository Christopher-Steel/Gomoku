#include "GUIPauseState.h"
#include "GameState.h"

#include <iostream>

GUIPauseState::GUIPauseState(GameAction *gameAction) : AState(gameAction)
{
	_isBlocking = false;
	_state = Gomoku::PauseMenu::CONTINUE;
}

GUIPauseState::~GUIPauseState()
{
}

void						GUIPauseState::initialize()
{
	_gameAction->factory.createPauseMenu(_id, _world, _gameAction->getScreenSize());
}

void						GUIPauseState::stop(void) {}


bool						GUIPauseState::handleKeyState()
{
	return (true);
}

bool						GUIPauseState::handleKeyEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int		prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			if ((_state--) == 0)
				_state = Gomoku::PauseMenu::EXIT;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Down:
			if ((++_state) == Gomoku::PauseMenu::EXIT + 1)
				_state = Gomoku::PauseMenu::CONTINUE;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Escape:
			_gameAction->popState();
			return (false);

		case sf::Keyboard::Return:
			if (_state == Gomoku::PauseMenu::CONTINUE)
			{
				_gameAction->popState();
				return (false);
			}
			else
			{
				_gameAction->popState();
				_gameAction->popState();
				return (false);
			}
		default:
			return (true);
		}
	}



	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			int x = event.mouseButton.x;
			int y = event.mouseButton.y;
    		if (x > 430 && x < 850 && y > 180 && y < 250)
    		{
    			_gameAction->popState();
				return (true);
    		}
    		if (x > 560 && x < 710 && y > 320 && y < 380)
    		{
    			_gameAction->popState();
    			_gameAction->popState();
				return (true);
    		}
		}
	}



	if (event.type == sf::Event::MouseMoved) {
		int x = event.mouseMove.x;
		int y = event.mouseMove.y;
		unsigned int			prev = _state;
		if (x > 430 && x < 850 && y > 180 && y < 250)
		{
			if (_state != Gomoku::PauseMenu::CONTINUE) {
				_state = Gomoku::PauseMenu::CONTINUE;
				_world.textComponents[_id[_state]]->highlighted = true;
				_world.textComponents[_id[prev]]->highlighted = false;
			}
		}
		if (x > 560 && x < 720 && y > 320 && y < 380)
		{
			if (_state != Gomoku::PauseMenu::EXIT) {
				_state = Gomoku::PauseMenu::EXIT;
				_world.textComponents[_id[_state]]->highlighted = true;
				_world.textComponents[_id[prev]]->highlighted = false;
			}
		}
	}


	return (true);
}