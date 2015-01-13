#include "GUIEndState.h"
#include "GameState.h"

GUIEndState::GUIEndState(GameAction *gameAction, const Result &result) : AState(gameAction)
{
	(result == WHITE) ? _result = "White Player Win !": _result;
	(result == BLACK) ? _result = "Black Player Win !": _result;
	(result == AI) ? _result = "No One Win !": _result;
	_isBlocking = false;
	_state = Gomoku::EndMenu::EXIT;
}

GUIEndState::~GUIEndState()
{
}

void						GUIEndState::initialize()
{
	_gameAction->factory.createEndMenu(_id, _world, _gameAction->getScreenSize(), _result);
}

bool						GUIEndState::handleKeyEvent(const sf::Event &event)
{
	_state = Gomoku::EndMenu::EXIT;
	_world.textComponents[_id[_state]]->highlighted = true;
	if (event.type == sf::Event::KeyPressed)
	{
		//unsigned int		prev = _state;

		switch (event.key.code)
		{
		case sf::Keyboard::Return:
			if (_state == Gomoku::EndMenu::EXIT)
			{
				_gameAction->popState();
				_gameAction->popState();
				return (false);
			}
		default:
			return (true);
		}
	}

	return (true);
}