#include "GUIState.h"
#include "GameState.h"
#include "GUIEndState.h"

#include <iostream>

GUIState::GUIState(Game *game) : AState(game)
{
	_isBlocking = true;
	_state = Gomoku::MainMenu::PLAYERPLAYER;
	_game = game;
}

GUIState::~GUIState()
{
}

void						GUIState::initialize()
{
	_game->factory.createMainMenu(_id, _world, _game->getScreenSize());
}

void						GUIState::stop(void) {}

bool						GUIState::handleKeyState()
{
	return (true);
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
				_game->pushState(new GameState(_game, Gomoku::MainMenu::PLAYERPLAYER));
				return (true);
			}
			else if (_state == Gomoku::MainMenu::PLAYERIA)
			{
				_game->pushState(new GameState(_game, Gomoku::MainMenu::PLAYERIA));
				return (true);
			}
			else
			{
				_game->popState();
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
    			_game->pushState(new GameState(_game, Gomoku::MainMenu::PLAYERPLAYER));
				return (true);
    		}
    		if (x > 400 && x < 1000 && y > 330 && y < 390)
    		{
    			_game->pushState(new GameState(_game, Gomoku::MainMenu::PLAYERIA));
				return (true);
    		}
			if (x > 550 && x < 860 && y > 480 && y < 530)
    		{
    			_game->popState();
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