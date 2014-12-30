#include "GUIPauseState.h"
#include "GameState.h"

GUIPauseState::GUIPauseState(Game *game) : AState(game)
{
	_isBlocking = false;
	_state = Gomoku::PauseMenu::CONTINUE;
}

GUIPauseState::~GUIPauseState()
{
}

void						GUIPauseState::initialize()
{
	_game->factory.createPauseMenu(_id, _world, _game->getScreenSize());
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
			_game->popState();
			return (false);

		case sf::Keyboard::Return:
			if (_state == Gomoku::PauseMenu::CONTINUE)
			{
				_game->popState();
				return (false);
			}
			else
			{
				_game->popState();
				_game->popState();
				return (false);
			}
		default:
			return (true);
		}
	}

	return (true);
}