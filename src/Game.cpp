#include <stack>

#include "Game.h"
#include "GameState.h"
#include "GUIState.h"

Game::Game() : factory(_resourceManager),  _window(NULL)
{
}

Game::~Game()
{
}

bool										Game::initialize(const sf::Vector2u &size, const std::string &title)
{
	_window = new sf::RenderWindow(sf::VideoMode(1280, 920), title, sf::Style::Default);

	if (!_window->isOpen())
		return (false);

	if (!this->loadTextures() || !this->loadFonts())
		return (false);

	this->pushState(new GUIState(this));
	return (true);
}

void										Game::run()
{
	sf::Event								event;
	std::vector<AState *>::reverse_iterator	rit;
	AState									*state;
	std::stack<AState *>					drawStack;

	while (_window->isOpen())
	{
		if (_states.empty())
			return;

		state = _states.back();
		while (_window->pollEvent(event))
		{
			if (!state->handleKeyEvent(event))
				break;
		}

		state->handleKeyState();
		_window->clear();

		for (rit = _states.rbegin(); rit != _states.rend(); ++rit)
		{
			state = *rit;
			state->update();
			drawStack.push(state);
			if (state->isBlocking())
				break;
		}

		while (!drawStack.empty())
		{
			drawStack.top()->draw(_window);
			drawStack.pop();
		}

		_window->display();
	}
}

void										Game::exit()
{
	if (_window != NULL)
	{
		_window->close();
		delete (_window);
	}
}

void										Game::pushState(AState *state)
{
	state->initialize();
	_states.push_back(state);
}

void										Game::popState()
{
	_states.back()->stop();
	_states.pop_back();
}

sf::Vector2u								Game::getScreenSize() const
{
	return (_window->getSize());
}

bool										Game::loadTextures()
{
	std::string								textures[7] =
	{
		"ressources/background.png",
		"ressources/white.png",
		"ressources/black.png",
		"ressources/jvsia.png",
		"ressources/jvsj.png",
		"ressources/goban.png",
		"ressources/unicolor.png"
	};

	for (unsigned int i = 0; i != 7; ++i)
	{
		if (!_resourceManager.loadTexture(textures[i]))
			return (false);
	}

	return (true);
}

bool										Game::loadFonts()
{
	std::string								fonts[1] =
	{
		"fonts/go3v2.ttf",
	};

	for (unsigned int i = 0; i != 1; ++i)
	{
		if (!_resourceManager.loadFont(fonts[i]))
			return (false);
	}

	return (true);
}