#pragma once

#include "World.h"
#include "ResourceManager.h"
#include "GameEnums.h"

class										GameSpecificFactory
{
public:
	typedef void							(GameSpecificFactory::*projectileCreator)(unsigned int *id, const unsigned int weapon, World &world, const sf::Vector2u &screenSize);

	GameSpecificFactory(ResourceManager &resourceManager);

	// MENUS

	void									createMainMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createLoadMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createPauseMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createEndMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize, const std::string &result);
	unsigned int							createGameBlackStone(World &world, const sf::Vector2f &pos);
	unsigned int							createGameWhiteStone(World &world, const sf::Vector2f &pos);


	// GAME

	void									createGameBackground(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createHUD(unsigned int *id, World &world, const sf::Vector2u &screenSize);
	void									createPlayer(unsigned int *id, World &world);

private:
	GameSpecificFactory();

	ResourceManager							&_resourceManager;
};