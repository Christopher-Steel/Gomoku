#include "GameSpecificFactory.h"

GameSpecificFactory::GameSpecificFactory(ResourceManager &resourceManager) : _resourceManager(resourceManager)
{
	createProjectile[0] = &GameSpecificFactory::createMissileProjectile;
	createProjectile[1] = &GameSpecificFactory::createLaserProjectile;
}

// MAIN MENU

void								GameSpecificFactory::createMainMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[RType::MainMenu::BACKGROUND] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::MainMenu::BACKGROUND], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/menu_background.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(id[RType::MainMenu::BACKGROUND], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f()));

	id[RType::MainMenu::TITLE] = world.createEmptyEntity();
	world.addTextComponent(id[RType::MainMenu::TITLE], ComponentFactory::createTextComponent("R-TYPE", _resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 120, sf::Color(13, 205, 248, 255)));
	world.addTransformComponent(id[RType::MainMenu::TITLE], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, 10.0f)));

	id[RType::MainMenu::CONNECT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::MainMenu::CONNECT], ComponentFactory::createTextComponent("Connect", _resourceManager.getFont("fonts/SPACEBAR.ttf"), true, true, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[RType::MainMenu::CONNECT], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, screenSize.y / 3.0f)));

	id[RType::MainMenu::EXIT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::MainMenu::EXIT], ComponentFactory::createTextComponent("Quit", _resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[RType::MainMenu::EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, screenSize.y / 3.0f + 150.0f)));
}

// LOAD MENU

void								GameSpecificFactory::createLoadMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[RType::LobbyMenu::BACKGROUND] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::LobbyMenu::BACKGROUND], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/menu_background.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(id[RType::LobbyMenu::BACKGROUND], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	id[RType::LobbyMenu::TEXT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::LobbyMenu::TEXT], ComponentFactory::createTextComponent("Waiting Gamers ...", _resourceManager.getFont("fonts/BMSPA.ttf"), true, true, 72, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[RType::LobbyMenu::TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f)));

	id[RType::LobbyMenu::LOAD_ICON] = world.createEmptyEntity();
	world.addSpinComponent(id[RType::LobbyMenu::LOAD_ICON], ComponentFactory::createSpinComponent(50, 1));
	world.addRenderComponent(id[RType::LobbyMenu::LOAD_ICON], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/load_icon.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(id[RType::LobbyMenu::LOAD_ICON], ComponentFactory::createTransformComponent(sf::Vector2f(175, 175), sf::Vector2f(screenSize.x - screenSize.x / 2.0f - 87.5f, screenSize.y / 2 + 100.0f)));
}

// PAUSE MENU

void								GameSpecificFactory::createPauseMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[RType::PauseMenu::FILTER] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::PauseMenu::FILTER], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color(0, 0, 0, 150)));
	world.addTransformComponent(id[RType::PauseMenu::FILTER], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	id[RType::PauseMenu::CONTINUE] = world.createEmptyEntity();
	world.addTextComponent(id[RType::PauseMenu::CONTINUE], ComponentFactory::createTextComponent("Continue", _resourceManager.getFont("fonts/SPACEBAR.ttf"), true, true, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[RType::PauseMenu::CONTINUE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f)));

	id[RType::PauseMenu::EXIT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::PauseMenu::EXIT], ComponentFactory::createTextComponent("Quit", _resourceManager.getFont("fonts/SPACEBAR.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[RType::PauseMenu::EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f + 150.0f)));
}

// END MENU

void								GameSpecificFactory::createEndMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize, const std::string &result)
{
	id[RType::EndMenu::FILTER] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::EndMenu::FILTER], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color(0, 0, 0, 150)));
	world.addTransformComponent(id[RType::EndMenu::FILTER], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	id[RType::EndMenu::RESULT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::EndMenu::RESULT], ComponentFactory::createTextComponent(result, _resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 80, sf::Color::White));
	world.addTransformComponent(id[RType::EndMenu::RESULT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 100.0f)));

	id[RType::EndMenu::SCORE] = world.createEmptyEntity();
	world.addTextComponent(id[RType::EndMenu::SCORE], ComponentFactory::createTextComponent("Score :", _resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 38, sf::Color::White));
	world.addTransformComponent(id[RType::EndMenu::SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, screenSize.y - screenSize.y / 2.0f)));

	id[RType::EndMenu::EXIT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::EndMenu::EXIT], ComponentFactory::createTextComponent("Press Enter To Quit", _resourceManager.getFont("fonts/BMSPA.ttf"), true, true, 18, sf::Color::White));
	world.addTransformComponent(id[RType::EndMenu::EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y - screenSize.y / 3.0f)));
}

// GAME BACKGROUND

void								GameSpecificFactory::createGameBackground(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[RType::GameBackground::DEFAULT] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::GameBackground::DEFAULT], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/background.png"), RenderComponent::Plane::BACKGROUND));
	world.addTransformComponent(id[RType::GameBackground::DEFAULT], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));
	world.addScrollComponent(id[RType::GameBackground::DEFAULT], ComponentFactory::createScrollComponent(20.0f));

	id[RType::GameBackground::REVERSED] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::GameBackground::REVERSED], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/background_reversed.png"), RenderComponent::Plane::BACKGROUND));
	world.addTransformComponent(id[RType::GameBackground::REVERSED], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(static_cast<float>(screenSize.x), 0.0f)));
	world.addScrollComponent(id[RType::GameBackground::REVERSED], ComponentFactory::createScrollComponent(20.0f));
}

// HUD

void								GameSpecificFactory::createHUD(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[RType::HUD::SHIELD_TEXT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::HUD::SHIELD_TEXT], ComponentFactory::createTextComponent("Shield", _resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	world.addTransformComponent(id[RType::HUD::SHIELD_TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 38.0f)));

	id[RType::HUD::SHIELDBAR] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::HUD::SHIELDBAR], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color(13, 205, 248)));
	world.addTransformComponent(id[RType::HUD::SHIELDBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 30.0f)));

	id[RType::HUD::LIFE_TEXT] = world.createEmptyEntity();
	world.addTextComponent(id[RType::HUD::LIFE_TEXT], ComponentFactory::createTextComponent("Life", _resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	world.addTransformComponent(id[RType::HUD::LIFE_TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 58.0f)));

	id[RType::HUD::LIFEBAR] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::HUD::LIFEBAR], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color::Green));
	world.addTransformComponent(id[RType::HUD::LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 50.0f)));

	id[RType::HUD::BOSS_LIFEBAR] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::HUD::BOSS_LIFEBAR], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color::Red));
	world.addTransformComponent(id[RType::HUD::BOSS_LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(500, 10), sf::Vector2f(screenSize.x / 2 - 250.0f, 50.0f)));

	id[RType::HUD::WEAPON_1] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::HUD::WEAPON_1], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/laser_icon.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(id[RType::HUD::WEAPON_1], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f, screenSize.y - 70.0f)));

	id[RType::HUD::WEAPON_2] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::HUD::WEAPON_2], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/mine_icon.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(id[RType::HUD::WEAPON_2], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f + 70, screenSize.y - 70.0f)));

	id[RType::HUD::WEAPON_3] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::HUD::WEAPON_3], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/missile_icon.png"), RenderComponent::Plane::HUD, sf::Color::Green));
	world.addTransformComponent(id[RType::HUD::WEAPON_3], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f - 70, screenSize.y - 70.0f)));

	id[RType::HUD::SCORE] = world.createEmptyEntity();
	world.addTextComponent(id[RType::HUD::SCORE], ComponentFactory::createTextComponent("Score : 0", _resourceManager.getFont("fonts/BMSPA.ttf"), true, false, 18, sf::Color(255, 255, 255, 255)));
	world.addTransformComponent(id[RType::HUD::SCORE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0, 15.0f)));
}

// PLAYER

void								GameSpecificFactory::createPlayer(unsigned int *id, World &world)
{
	std::set<unsigned int>			parts;

	std::vector<const sf::Texture * const> deathAnimation;

	deathAnimation.push_back(_resourceManager.getTexture("textures/explosion0.png"));
	deathAnimation.push_back(_resourceManager.getTexture("textures/explosion1.png"));
	deathAnimation.push_back(_resourceManager.getTexture("textures/explosion2.png"));
	deathAnimation.push_back(_resourceManager.getTexture("textures/explosion3.png"));
	deathAnimation.push_back(_resourceManager.getTexture("textures/explosion4.png"));
	deathAnimation.push_back(_resourceManager.getTexture("textures/explosion5.png"));

	id[RType::Player::SHIP] = world.createEmptyEntity();
	world.addRenderComponent(id[RType::Player::SHIP], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/hero.png"), RenderComponent::Plane::DEFAULT));
	world.addTransformComponent(id[RType::Player::SHIP], ComponentFactory::createTransformComponent(sf::Vector2f(1021, 748), sf::Vector2f(0, 0), sf::Vector2f(0.15f, 0.15f)));
	world.addMovementComponent(id[RType::Player::SHIP], ComponentFactory::createMovementComponent(500, sf::Vector2f()));
	world.addInfoComponent(id[RType::Player::SHIP], ComponentFactory::createInfoComponent(500, 200, 0, deathAnimation, sf::seconds(0.1f)));

	id[RType::Player::ENGINE_1] = world.createParticleEffect(25, true, _resourceManager.getTexture("textures/fireMotor.png"), sf::Vector2f(-18, 0), sf::Vector2f(0.3f, 0.3f));
	world.addParentComponent(id[RType::Player::ENGINE_1], ComponentFactory::createParentComponent(id[RType::Player::SHIP]));
	world.emitterComponents[id[RType::Player::ENGINE_1]]->lifetimeInterval = sf::Vector2f(0.1f, 0.2f);
	world.emitterComponents[id[RType::Player::ENGINE_1]]->propagationInterval = sf::Vector2f(170.0f, 190.0f);
	world.emitterComponents[id[RType::Player::ENGINE_1]]->velocityInterval = sf::Vector2f(100.0f, 200.0f);

	id[RType::Player::ENGINE_2] = world.createParticleEffect(25, true, _resourceManager.getTexture("textures/fireMotor.png"), sf::Vector2f(-18, 81), sf::Vector2f(0.3f, 0.3f));
	world.addParentComponent(id[RType::Player::ENGINE_2], ComponentFactory::createParentComponent(id[RType::Player::SHIP]));
	world.emitterComponents[id[RType::Player::ENGINE_2]]->lifetimeInterval = sf::Vector2f(0.1f, 0.2f);
	world.emitterComponents[id[RType::Player::ENGINE_2]]->propagationInterval = sf::Vector2f(170.0f, 190.0f);
	world.emitterComponents[id[RType::Player::ENGINE_2]]->velocityInterval = sf::Vector2f(100.0f, 200.0f);

	id[RType::Player::WEAPON_1] = world.createEmptyEntity();
	world.addTransformComponent(id[RType::Player::WEAPON_1], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(20.0f, 8.0f)));
	world.addParentComponent(id[RType::Player::WEAPON_1], ComponentFactory::createParentComponent(id[RType::Player::SHIP]));
	world.addWeaponComponent(id[RType::Player::WEAPON_1], ComponentFactory::createWeaponComponent(sf::seconds(0.2f), id[RType::Player::SHIP], RType::Projectile::MISSILE));

	id[RType::Player::WEAPON_2] = world.createEmptyEntity();
	world.addTransformComponent(id[RType::Player::WEAPON_2], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(20.0f, 8.0f)));
	world.addParentComponent(id[RType::Player::WEAPON_2], ComponentFactory::createParentComponent(id[RType::Player::SHIP]));
	world.addWeaponComponent(id[RType::Player::WEAPON_2], ComponentFactory::createWeaponComponent(sf::seconds(20.0f), id[RType::Player::SHIP], RType::Projectile::LASER));
	world.addChildrenComponent(id[RType::Player::WEAPON_2], ComponentFactory::createChildrenComponent(std::set<unsigned int>()));

	parts.insert(id[RType::Player::ENGINE_1]);
	parts.insert(id[RType::Player::ENGINE_2]);
	parts.insert(id[RType::Player::WEAPON_1]);
	parts.insert(id[RType::Player::WEAPON_2]);
	world.addChildrenComponent(id[RType::Player::SHIP], ComponentFactory::createChildrenComponent(parts));
}