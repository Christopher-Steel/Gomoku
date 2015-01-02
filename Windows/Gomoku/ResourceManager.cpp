#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (std::map<const std::string, const sf::Texture * const>::iterator it = _textures.begin(); it != _textures.end(); ++it)
		delete (it->second);
	_textures.clear();

	for (std::map<const std::string, const sf::Font * const>::iterator it = _fonts.begin(); it != _fonts.end(); ++it)
		delete (it->second);
	_fonts.clear();
}

bool																	ResourceManager::loadTexture(const std::string &path)
{
	sf::Texture	* const													texture = new sf::Texture();
	
	if (!texture->loadFromFile(path))
		return (false);
	texture->setSmooth(true);
	_textures.insert(std::pair<const std::string, const sf::Texture * const>(path, texture));
	return (true);
}

bool																	ResourceManager::loadFont(const std::string &path)
{
	sf::Font * const													font = new sf::Font();

	if (!font->loadFromFile(path))
		return (false);
	_fonts.insert(std::pair<const std::string, const sf::Font * const>(path, font));
	return (true);
}

void																	ResourceManager::unloadTexture(const std::string &id)
{
	std::map<const std::string, const sf::Texture * const>::iterator	it;

	if ((it = _textures.find(id)) != _textures.end())
	{
		delete (it->second);
		_textures.erase(it);
	}
}

void																	ResourceManager::unloadFont(const std::string &id)
{
	std::map<const std::string, const sf::Font * const>::iterator		it;

	if ((it = _fonts.find(id)) != _fonts.end())
	{
		delete (it->second);
		_fonts.erase(it);
	}
}

const sf::Texture * const												ResourceManager::getTexture(const std::string &id) const
{
	if (_textures.find(id) == _textures.end())
		return (NULL);
	return (_textures.at(id));
}

const sf::Font * const													ResourceManager::getFont(const std::string &id) const
{
	if (_fonts.find(id) == _fonts.end())
		return (NULL);
	return (_fonts.at(id));
}