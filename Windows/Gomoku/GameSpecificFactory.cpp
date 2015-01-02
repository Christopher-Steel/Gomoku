#include "GameSpecificFactory.h"

GameSpecificFactory::GameSpecificFactory(ResourceManager &resourceManager) : _resourceManager(resourceManager)
{
	// createProjectile[0] = &GameSpecificFactory::createMissileProjectile;
	// createProjectile[1] = &GameSpecificFactory::createLaserProjectile;
}

// MAIN MENU

void								GameSpecificFactory::createMainMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[Gomoku::MainMenu::BACKGROUND] = world.createEmptyEntity();
	world.addRenderComponent(id[Gomoku::MainMenu::BACKGROUND], ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/background.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(id[Gomoku::MainMenu::BACKGROUND], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f()));

	id[Gomoku::MainMenu::TITLE] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::MainMenu::TITLE], ComponentFactory::createTextComponent("Gomoku", _resourceManager.getFont("fonts/go3v2.ttf"), true, false, 120, sf::Color::Black));
	world.addTransformComponent(id[Gomoku::MainMenu::TITLE], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, 0.0f)));

	id[Gomoku::MainMenu::PLAYERPLAYER] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::MainMenu::PLAYERPLAYER], ComponentFactory::createTextComponent("Player VS Player", _resourceManager.getFont("fonts/go3v2.ttf"), true, true, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[Gomoku::MainMenu::PLAYERPLAYER], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, 150.0f)));

	id[Gomoku::MainMenu::PLAYERIA] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::MainMenu::PLAYERIA], ComponentFactory::createTextComponent("Player VS IA", _resourceManager.getFont("fonts/go3v2.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[Gomoku::MainMenu::PLAYERIA], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, 300.0f)));

	id[Gomoku::MainMenu::EXIT] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::MainMenu::EXIT], ComponentFactory::createTextComponent("Quit", _resourceManager.getFont("fonts/go3v2.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[Gomoku::MainMenu::EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, 450.0f)));
}

// LOAD MENU

void								GameSpecificFactory::createLoadMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	// id[Gomoku::LobbyMenu::BACKGROUND] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::LobbyMenu::BACKGROUND], ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/background.png"), RenderComponent::Plane::HUD));
	// world.addTransformComponent(id[Gomoku::LobbyMenu::BACKGROUND], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	// id[Gomoku::LobbyMenu::TEXT] = world.createEmptyEntity();
	// world.addTextComponent(id[Gomoku::LobbyMenu::TEXT], ComponentFactory::createTextComponent("Waiting Gamers ...", _resourceManager.getFont("fonts/BMSPA.ttf"), true, true, 72, sf::Color(255, 255, 255, 150)));
	// world.addTransformComponent(id[Gomoku::LobbyMenu::TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y / 3.0f)));

	// id[Gomoku::LobbyMenu::LOAD_ICON] = world.createEmptyEntity();
	// //world.addSpinComponent(id[Gomoku::LobbyMenu::LOAD_ICON], ComponentFactory::createSpinComponent(50, 1));
	// world.addRenderComponent(id[Gomoku::LobbyMenu::LOAD_ICON], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/load_icon.png"), RenderComponent::Plane::HUD));
	// world.addTransformComponent(id[Gomoku::LobbyMenu::LOAD_ICON], ComponentFactory::createTransformComponent(sf::Vector2f(175, 175), sf::Vector2f(screenSize.x - screenSize.x / 2.0f - 87.5f, screenSize.y / 2 + 100.0f)));
}

// PAUSE MENU

void								GameSpecificFactory::createPauseMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[Gomoku::PauseMenu::FILTER] = world.createEmptyEntity();
	world.addRenderComponent(id[Gomoku::PauseMenu::FILTER], ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/unicolor.png"), RenderComponent::Plane::HUD, sf::Color(0, 0, 0, 150)));
	world.addTransformComponent(id[Gomoku::PauseMenu::FILTER], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	id[Gomoku::PauseMenu::CONTINUE] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::PauseMenu::CONTINUE], ComponentFactory::createTextComponent("Continue", _resourceManager.getFont("fonts/go3v2.ttf"), true, true, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[Gomoku::PauseMenu::CONTINUE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 150.0f)));

	id[Gomoku::PauseMenu::EXIT] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::PauseMenu::EXIT], ComponentFactory::createTextComponent("Quit", _resourceManager.getFont("fonts/go3v2.ttf"), true, false, 80, sf::Color(255, 255, 255, 150)));
	world.addTransformComponent(id[Gomoku::PauseMenu::EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 300.0f)));
}

// END MENU

void								GameSpecificFactory::createEndMenu(unsigned int *id, World &world, const sf::Vector2u &screenSize, const std::string &result)
{
	id[Gomoku::EndMenu::FILTER] = world.createEmptyEntity();
	world.addRenderComponent(id[Gomoku::EndMenu::FILTER], ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/unicolor.png"), RenderComponent::Plane::HUD, sf::Color(0, 0, 0, 150)));
	world.addTransformComponent(id[Gomoku::EndMenu::FILTER], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));

	id[Gomoku::EndMenu::RESULT] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::EndMenu::RESULT], ComponentFactory::createTextComponent(result, _resourceManager.getFont("fonts/go3v2.ttf"), true, false, 80, sf::Color::White));
	world.addTransformComponent(id[Gomoku::EndMenu::RESULT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 350.0f)));

	id[Gomoku::EndMenu::EXIT] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::EndMenu::EXIT], ComponentFactory::createTextComponent("Press Enter To Quit", _resourceManager.getFont("fonts/go3v2.ttf"), true, true, 18, sf::Color::White));
	world.addTransformComponent(id[Gomoku::EndMenu::EXIT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, screenSize.y - screenSize.y / 3.0f)));
}

// GAME BACKGROUND

void								GameSpecificFactory::createGameBackground(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[Gomoku::GameBackground::DEFAULT] = world.createEmptyEntity();
	world.addRenderComponent(id[Gomoku::GameBackground::DEFAULT], ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/background.png"), RenderComponent::Plane::BACKGROUND));
	world.addTransformComponent(id[Gomoku::GameBackground::DEFAULT], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(0.0f, 0.0f)));
	//world.addScrollComponent(id[Gomoku::GameBackground::DEFAULT], ComponentFactory::createScrollComponent(20.0f));

	// id[Gomoku::GameBackground::REVERSED] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::GameBackground::REVERSED], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/background_reversed.png"), RenderComponent::Plane::BACKGROUND));
	// world.addTransformComponent(id[Gomoku::GameBackground::REVERSED], ComponentFactory::createTransformComponent(sf::Vector2f(screenSize), sf::Vector2f(static_cast<float>(screenSize.x), 0.0f)));
	//world.addScrollComponent(id[Gomoku::GameBackground::REVERSED], ComponentFactory::createScrollComponent(20.0f));
}

unsigned int								GameSpecificFactory::createGameBlackStone(World &world, const sf::Vector2f &pos)
{
	unsigned int tmp = world.createEmptyEntity();
	world.addRenderComponent(tmp, ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/black.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(tmp, ComponentFactory::createTransformComponent(sf::Vector2f(42,42), sf::Vector2f(pos)));
	return (tmp);
}
unsigned int								GameSpecificFactory::createGameWhiteStone(World &world, const sf::Vector2f &pos)
{
	unsigned int tmp = world.createEmptyEntity();
	world.addRenderComponent(tmp, ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/white.png"), RenderComponent::Plane::HUD));
	world.addTransformComponent(tmp, ComponentFactory::createTransformComponent(sf::Vector2f(42,42), sf::Vector2f(pos)));
	return (tmp);
}

// HUD

void								GameSpecificFactory::createHUD(unsigned int *id, World &world, const sf::Vector2u &screenSize)
{
	id[Gomoku::GAME::TITLE] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::GAME::TITLE], ComponentFactory::createTextComponent("Gomoku", _resourceManager.getFont("fonts/go3v2.ttf"), true, false, 120, sf::Color::Black));
	world.addTransformComponent(id[Gomoku::GAME::TITLE], ComponentFactory::createTransformComponent(sf::Vector2f(), sf::Vector2f(0.0f, 0.0f)));


	id[Gomoku::GAME::SCOREWHITE] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::GAME::SCOREWHITE], ComponentFactory::createTextComponent("Stone White : ", _resourceManager.getFont("fonts/go3v2.ttf"), false, false, 28, sf::Color::Black));
	world.addTransformComponent(id[Gomoku::GAME::SCOREWHITE], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 50.0f)));

	id[Gomoku::GAME::SCOREBLACK] = world.createEmptyEntity();
	world.addTextComponent(id[Gomoku::GAME::SCOREBLACK], ComponentFactory::createTextComponent("Stone Black : ", _resourceManager.getFont("fonts/go3v2.ttf"), false, false, 28, sf::Color::Black));
	world.addTransformComponent(id[Gomoku::GAME::SCOREBLACK], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 100.0f)));

	// id[Gomoku::HUD::SHIELDBAR] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::HUD::SHIELDBAR], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color(13, 205, 248)));
	// world.addTransformComponent(id[Gomoku::HUD::SHIELDBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 30.0f)));

	// id[Gomoku::HUD::LIFE_TEXT] = world.createEmptyEntity();
	// world.addTextComponent(id[Gomoku::HUD::LIFE_TEXT], ComponentFactory::createTextComponent("Life", _resourceManager.getFont("fonts/BMSPA.ttf"), false, false, 18, sf::Color(255, 255, 255, 255)));
	// world.addTransformComponent(id[Gomoku::HUD::LIFE_TEXT], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(25.0f, screenSize.y - 58.0f)));

	// id[Gomoku::HUD::LIFEBAR] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::HUD::LIFEBAR], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color::Green));
	// world.addTransformComponent(id[Gomoku::HUD::LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(200, 10), sf::Vector2f(120.0f, screenSize.y - 50.0f)));

	// id[Gomoku::HUD::BOSS_LIFEBAR] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::HUD::BOSS_LIFEBAR], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/unicolor.png"), RenderComponent::Plane::HUD, sf::Color::Red));
	// world.addTransformComponent(id[Gomoku::HUD::BOSS_LIFEBAR], ComponentFactory::createTransformComponent(sf::Vector2f(500, 10), sf::Vector2f(screenSize.x / 2 - 250.0f, 50.0f)));

	// id[Gomoku::HUD::WEAPON_1] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::HUD::WEAPON_1], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/laser_icon.png"), RenderComponent::Plane::HUD));
	// world.addTransformComponent(id[Gomoku::HUD::WEAPON_1], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f, screenSize.y - 70.0f)));

	// id[Gomoku::HUD::WEAPON_2] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::HUD::WEAPON_2], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/mine_icon.png"), RenderComponent::Plane::HUD));
	// world.addTransformComponent(id[Gomoku::HUD::WEAPON_2], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f + 70, screenSize.y - 70.0f)));

	// id[Gomoku::HUD::WEAPON_3] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::HUD::WEAPON_3], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/missile_icon.png"), RenderComponent::Plane::HUD, sf::Color::Green));
	// world.addTransformComponent(id[Gomoku::HUD::WEAPON_3], ComponentFactory::createTransformComponent(sf::Vector2f(50, 50), sf::Vector2f(screenSize.x - screenSize.x / 7.0f - 70, screenSize.y - 70.0f)));

	id[Gomoku::GAME::GOBAN] = world.createEmptyEntity();
	world.addRenderComponent(id[Gomoku::GAME::GOBAN], ComponentFactory::createRenderComponent(_resourceManager.getTexture("ressources/goban.png"), RenderComponent::Plane::DEFAULT));
	world.addTransformComponent(id[Gomoku::GAME::GOBAN], ComponentFactory::createTransformComponent(sf::Vector2f(1024, 768), sf::Vector2f(150,100)));
}

// PLAYER

void								GameSpecificFactory::createPlayer(unsigned int *id, World &world)
{
	// std::set<unsigned int>			parts;

	// std::vector<const sf::Texture * const> deathAnimation;

	// deathAnimation.push_back(_resourceManager.getTexture("textures/explosion0.png"));
	// deathAnimation.push_back(_resourceManager.getTexture("textures/explosion1.png"));
	// deathAnimation.push_back(_resourceManager.getTexture("textures/explosion2.png"));
	// deathAnimation.push_back(_resourceManager.getTexture("textures/explosion3.png"));
	// deathAnimation.push_back(_resourceManager.getTexture("textures/explosion4.png"));
	// deathAnimation.push_back(_resourceManager.getTexture("textures/explosion5.png"));

	// id[Gomoku::Player::SHIP] = world.createEmptyEntity();
	// world.addRenderComponent(id[Gomoku::Player::SHIP], ComponentFactory::createRenderComponent(_resourceManager.getTexture("textures/hero.png"), RenderComponent::Plane::DEFAULT));
	// world.addTransformComponent(id[Gomoku::Player::SHIP], ComponentFactory::createTransformComponent(sf::Vector2f(1021, 748), sf::Vector2f(0, 0), sf::Vector2f(0.15f, 0.15f)));
	// world.addMovementComponent(id[Gomoku::Player::SHIP], ComponentFactory::createMovementComponent(500, sf::Vector2f()));
	// world.addInfoComponent(id[Gomoku::Player::SHIP], ComponentFactory::createInfoComponent(500, 200, 0, deathAnimation, sf::seconds(0.1f)));

	// id[Gomoku::Player::ENGINE_1] = world.createParticleEffect(25, true, _resourceManager.getTexture("textures/fireMotor.png"), sf::Vector2f(-18, 0), sf::Vector2f(0.3f, 0.3f));
	// world.addParentComponent(id[Gomoku::Player::ENGINE_1], ComponentFactory::createParentComponent(id[Gomoku::Player::SHIP]));
	// world.emitterComponents[id[Gomoku::Player::ENGINE_1]]->lifetimeInterval = sf::Vector2f(0.1f, 0.2f);
	// world.emitterComponents[id[Gomoku::Player::ENGINE_1]]->propagationInterval = sf::Vector2f(170.0f, 190.0f);
	// world.emitterComponents[id[Gomoku::Player::ENGINE_1]]->velocityInterval = sf::Vector2f(100.0f, 200.0f);

	// id[Gomoku::Player::ENGINE_2] = world.createParticleEffect(25, true, _resourceManager.getTexture("textures/fireMotor.png"), sf::Vector2f(-18, 81), sf::Vector2f(0.3f, 0.3f));
	// world.addParentComponent(id[Gomoku::Player::ENGINE_2], ComponentFactory::createParentComponent(id[Gomoku::Player::SHIP]));
	// world.emitterComponents[id[Gomoku::Player::ENGINE_2]]->lifetimeInterval = sf::Vector2f(0.1f, 0.2f);
	// world.emitterComponents[id[Gomoku::Player::ENGINE_2]]->propagationInterval = sf::Vector2f(170.0f, 190.0f);
	// world.emitterComponents[id[Gomoku::Player::ENGINE_2]]->velocityInterval = sf::Vector2f(100.0f, 200.0f);

	// id[Gomoku::Player::WEAPON_1] = world.createEmptyEntity();
	// world.addTransformComponent(id[Gomoku::Player::WEAPON_1], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(20.0f, 8.0f)));
	// world.addParentComponent(id[Gomoku::Player::WEAPON_1], ComponentFactory::createParentComponent(id[Gomoku::Player::SHIP]));
	// world.addWeaponComponent(id[Gomoku::Player::WEAPON_1], ComponentFactory::createWeaponComponent(sf::seconds(0.2f), id[Gomoku::Player::SHIP], Gomoku::Projectile::MISSILE));

	// id[Gomoku::Player::WEAPON_2] = world.createEmptyEntity();
	// world.addTransformComponent(id[Gomoku::Player::WEAPON_2], ComponentFactory::createTransformComponent(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(20.0f, 8.0f)));
	// world.addParentComponent(id[Gomoku::Player::WEAPON_2], ComponentFactory::createParentComponent(id[Gomoku::Player::SHIP]));
	// world.addWeaponComponent(id[Gomoku::Player::WEAPON_2], ComponentFactory::createWeaponComponent(sf::seconds(20.0f), id[Gomoku::Player::SHIP], Gomoku::Projectile::LASER));
	// world.addChildrenComponent(id[Gomoku::Player::WEAPON_2], ComponentFactory::createChildrenComponent(std::set<unsigned int>()));

	// parts.insert(id[Gomoku::Player::ENGINE_1]);
	// parts.insert(id[Gomoku::Player::ENGINE_2]);
	// parts.insert(id[Gomoku::Player::WEAPON_1]);
	// parts.insert(id[Gomoku::Player::WEAPON_2]);
	// world.addChildrenComponent(id[Gomoku::Player::SHIP], ComponentFactory::createChildrenComponent(parts));
}