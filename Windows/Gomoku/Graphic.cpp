#include "Graphic.h"

Graphic::Graphic(sf::RenderWindow &window) : _window(window)
{
	_texture["background"] = new sf::Texture;
	_sprite["background"] = new sf::Sprite;
	_texture["title"] = new sf::Texture;
	_sprite["title"] = new sf::Sprite;
	_texture["plateau"] = new sf::Texture;
	_sprite["plateau"] = new sf::Sprite;
	_texture["blanc"] = new sf::Texture;
	_sprite["blanc"] = new sf::Sprite;
	_texture["noir"] = new sf::Texture;
	_sprite["noir"] = new sf::Sprite;
	_texture["jvsj"] = new sf::Texture;
	_sprite["jvsj"] = new sf::Sprite;
	_texture["jvsia"] = new sf::Texture;
	_sprite["jvsia"] = new sf::Sprite;
}

Graphic::~Graphic()
{

}

PlayerColor					Graphic::run()
{
	bool				player = false;
	Player				p;
	bool				menu = true;
	PlayerColor			plcl = PlayerColor::NONE;
	PlayerColor			plclTmp = PlayerColor::NONE;
	int 				tmpX;
	int 				tmpY;
	ModuleGame 			*_game = new ModuleGame();

	loadTexture();
	while (_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				if (!menu)
				{
					p.posX = sf::Mouse::getPosition(_window).x;
					p.posY = sf::Mouse::getPosition(_window).y;
					if ((p.posX >= 60 && p.posY >= 90) && (p.posX <= 966 && p.posY >= 90))
					{
						averagePosition(p, &tmpX, &tmpY);
						if (checkPosition(p) == true) {
							if ((plcl = _game->run(findX(p.posX - 64), findY(p.posY - 95), player)) == PlayerColor::END) {
								return plclTmp;
							} else if (plcl == PlayerColor::ERROR) {
							} else {
								plclTmp = plcl;
								putPion(p, player);
								player = !player;
							}
						}
						else {
							player = player;
						}
					}
				}
				else
				{
					if (_jvsj.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))))
					{
						menu = false;
						_game->initPlayer(PlayerType::HUMAN, PlayerType::HUMAN);
					}
					else if (_jvsia.contains(_window.mapPixelToCoords(sf::Mouse::getPosition(_window))))
					{
						menu = false;
						_game->initPlayer(PlayerType::HUMAN, PlayerType::HUMAN);
					}
				}
			}
		}
		_window.clear();
		if (!menu)
			draw();
		else
			drawMenu();
		_window.display();
	}
	return PlayerColor::END;
}

void					Graphic::draw()
{
	// _window.draw(*_sprite["background"]);
	// _window.draw(*_sprite["title"]);
	// _window.draw(*_sprite["plateau"]);
	for (std::vector<Player>::iterator it = _player1.begin(); it != _player1.end(); ++it)
		_window.draw(it->sprite);
	for (std::vector<Player>::iterator it = _player2.begin(); it != _player2.end(); ++it)
		_window.draw(it->sprite);
}

void					Graphic::clear() {
	_player1.clear();
	_player2.clear();
}

void					Graphic::loadTexture()
{
	if (!_texture["background"]->loadFromFile("ressources/background.png"))
		throw std::runtime_error("Failed load texture");
	_sprite["background"]->setTexture(*_texture["background"]);
	if (!_texture["title"]->loadFromFile("ressources/title.png"))
		throw std::runtime_error("Failed load texture");
	_sprite["title"]->setTexture(*_texture["title"]);
	if (!_texture["plateau"]->loadFromFile("ressources/plateau.png"))
		throw std::runtime_error("Failed load texture");
	_sprite["plateau"]->setTexture(*_texture["plateau"]);
	if (!_texture["blanc"]->loadFromFile("ressources/blanc.png"))
		throw std::runtime_error("Failed load texture");
	_sprite["blanc"]->setTexture(*_texture["blanc"]);
	if (!_texture["noir"]->loadFromFile("ressources/noir.png"))
		throw std::runtime_error("Failed load texture");
	_sprite["noir"]->setTexture(*_texture["noir"]);
	if (!_texture["jvsj"]->loadFromFile("ressources/jvsj.png"))
		throw std::runtime_error("Failed load texture");
	_sprite["jvsj"]->setTexture(*_texture["jvsj"]);
	_sprite["jvsj"]->setPosition(350, 220);
	_jvsj.height = _sprite["jvsj"]->getLocalBounds().height - 60;
	_jvsj.width = _sprite["jvsj"]->getLocalBounds().width - 50;
	_jvsj.left = 350 + 25;
	_jvsj.top = 220 + 30;
	if (!_texture["jvsia"]->loadFromFile("ressources/jvsia.png"))
		throw std::runtime_error("Failed load texture");
	_sprite["jvsia"]->setTexture(*_texture["jvsia"]);
	_sprite["jvsia"]->setPosition(350, 220 + _sprite["jvsia"]->getLocalBounds().height + 80);
	_jvsia.height = _sprite["jvsia"]->getLocalBounds().height - 60;
	_jvsia.width = _sprite["jvsia"]->getLocalBounds().width - 50;
	_jvsia.left = 350 + 25;
	_jvsia.top = 220 + 30 + _sprite["jvsia"]->getLocalBounds().height + 80;
}

void					Graphic::averagePosition(Player &p, int *x2, int *y2) {
	int					x;
	int					y;

	y = (p.posY - 95) % 35;
	x = (p.posX - 64) % 50;
	if (y <= (35 / 2))
		*y2 = p.posY - (y % 35);
	else
		*y2 = p.posY - (y % 35) + 35;
	if (x < (50 / 2))
		*x2 = p.posX - (x % 50);
	else
		*x2 = p.posX - (x % 50) + 50;
	p.posX = *x2;
	p.posY = *y2;
}

bool					Graphic::putPion(Player &p, bool player)
{
	int					x;
	int					y;

	averagePosition(p, &x, &y);
	if (player)
	{
		p.sprite = *_sprite["blanc"];
		p.sprite.setPosition(x - _sprite["blanc"]->getLocalBounds().width / 2, y - _sprite["blanc"]->getLocalBounds().height / 2);
		if (checkPosition(p) != false) {
			_player1.push_back(p);
			return (true);
		}
		else
			return (false);
	}
	else
	{
		p.sprite = *_sprite["noir"];
		p.sprite.setPosition(x - _sprite["noir"]->getLocalBounds().width / 2, y - _sprite["noir"]->getLocalBounds().height / 2);
		if (checkPosition(p) != false) {
			_player2.push_back(p);
			return (true);
		}
		else
			return (false);
	}
}

void					Graphic::drawMenu()
{
	_window.draw(*_sprite["background"]);
	_window.draw(*_sprite["title"]);
	_window.draw(*_sprite["jvsj"]);
	_window.draw(*_sprite["jvsia"]);
}

bool					Graphic::checkPosition(const Player &player) {
	bool	x = false;
	bool	y = false;

	for (std::vector<Player>::iterator it = _player1.begin(); it != _player1.end(); ++it) {
		if (it->posX == player.posX) {
			x = true;
			if (it->posY == player.posY)
				y = true;
			if (x == true && y == true)
				return (false);
		}
	}
	for (std::vector<Player>::iterator it = _player2.begin(); it != _player2.end(); ++it) {
		if (it->posX == player.posX) {
			x = true;
			if (it->posY == player.posY)
				y = true;
			if (x == true && y == true)
				return (false);
		}
	}
	return (true);
}

unsigned int 	Graphic::findX(unsigned int pos) {
	unsigned int tmp = pos;
	unsigned int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 50;	
	}
	return (ret);
}

unsigned int 	Graphic::findY(unsigned int pos) {
	unsigned int tmp = pos;
	unsigned int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 35;
	}
	return (ret);
}
