#include "Graphic.h"

#include <ostream>
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int						main()
{
	sf::RenderWindow	window(sf::VideoMode(1024, 768), "Gomoku");
	Graphic				*graphic = new Graphic(window);
	//Game				game;

	//Goban goban;

	//game.runGame();

//	game.run(PlayerType::HUMAN, PlayerType::HUMAN);
	//std::cout << "SFML" << std::endl;
	graphic->run();
	return 0;
}