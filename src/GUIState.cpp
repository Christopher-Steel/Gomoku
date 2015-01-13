#include "GUIState.h"
#include "GameState.h"
#include "GUIEndState.h"

#include <iostream>

GUIState::GUIState(GameAction *gameAction) : AState(gameAction)
{
	_isBlocking = true;
	_state = Gomoku::MainMenu::PLAYERPLAYER;
	_gameAction = gameAction;
}

GUIState::~GUIState()
{
}

void						GUIState::initialize()
{
	_gameAction->factory.createMainMenu(_id, _world, _gameAction->getScreenSize());
}

bool						GUIState::handleKeyEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		unsigned int			prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			if ((_state--) == 0)
				_state = Gomoku::MainMenu::EXIT;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Down:
			if ((++_state) == Gomoku::MainMenu::EXIT + 1)
				_state = Gomoku::MainMenu::PLAYERPLAYER;
			_world.textComponents[_id[_state]]->highlighted = true;
			_world.textComponents[_id[prev]]->highlighted = false;
			return(true);

		case sf::Keyboard::Return:
			if (_state == Gomoku::MainMenu::PLAYERPLAYER)
			{
				_gameAction->pushState(new GameState(_gameAction, Gomoku::MainMenu::PLAYERPLAYER));
				return (true);
			}
			else if (_state == Gomoku::MainMenu::PLAYERIA)
			{
				_gameAction->pushState(new GameState(_gameAction, Gomoku::MainMenu::PLAYERIA));
				return (true);
			}
			else
			{
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
    		if (x > 230 && x < 1040 && y > 180 && y < 250)
    		{
    			_gameAction->pushState(new GameState(_gameAction, Gomoku::MainMenu::PLAYERPLAYER));
				return (true);
    		}
    		if (x > 400 && x < 1000 && y > 330 && y < 390)
    		{
    			_gameAction->pushState(new GameState(_gameAction, Gomoku::MainMenu::PLAYERIA));
				return (true);
    		}
			if (x > 550 && x < 860 && y > 480 && y < 530)
    		{
    			_gameAction->popState();
				return (false);
    		}
		}
	}




	if (event.type == sf::Event::MouseMoved) {
		int x = event.mouseMove.x;
		int y = event.mouseMove.y;
		unsigned int			prev = _state;
		if (x > 230 && x < 1040 && y > 180 && y < 250)
		{
			if (_state != Gomoku::MainMenu::PLAYERPLAYER) {
				_state = Gomoku::MainMenu::PLAYERPLAYER;
				_world.textComponents[_id[_state]]->highlighted = true;
				_world.textComponents[_id[prev]]->highlighted = false;
			}
		}
		if (x > 400 && x < 1000 && y > 330 && y < 390)
		{
			if (_state != Gomoku::MainMenu::PLAYERIA) {
				_state = Gomoku::MainMenu::PLAYERIA;
				_world.textComponents[_id[_state]]->highlighted = true;
				_world.textComponents[_id[prev]]->highlighted = false;
			}
		}
		if (x > 550 && x < 860 && y > 480 && y < 530)
		{
			if (_state != Gomoku::MainMenu::EXIT) {
				_state = Gomoku::MainMenu::EXIT;
				_world.textComponents[_id[_state]]->highlighted = true;
				_world.textComponents[_id[prev]]->highlighted = false;
			}
		}
	}

	return (true);
}