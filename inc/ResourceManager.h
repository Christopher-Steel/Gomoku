#pragma once

#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class														ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	/* peut etre return la sf::Texture pour le load, et return une texture de debug si fail */
	bool													loadTexture(const std::string &path);
	bool													loadFont(const std::string &path);
	void													unloadTexture(const std::string &id);
	void													unloadFont(const std::string &id);
	const sf::Texture * const								getTexture(const std::string &id) const;
	const sf::Font * const									getFont(const std::string &id) const;
private:
	ResourceManager(const ResourceManager &rhs);
	ResourceManager &operator=(const ResourceManager &rhs);

	std::map<const std::string, const sf::Texture * const>	_textures;
	std::map<const std::string, const sf::Font * const>		_fonts;
};