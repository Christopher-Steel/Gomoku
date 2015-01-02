// #include "Graphic.h"
#include "AState.h"

#include <ostream>
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int						main()
{
		Game						game;

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	if (!game.initialize(sf::Vector2u(1280, 720), "Gomoku")) {
		return (EXIT_FAILURE);
	}
	game.run();
	game.exit();
	return (EXIT_SUCCESS);
	//sf::RenderWindow	window(sf::VideoMode(1024, 768), "Gomoku");
	// Graphic				*graphic = new Graphic(window);
	// PlayerColor			pl;
	//Game				game;

	//Goban goban;

	//game.runGame();

//	game.run(PlayerType::HUMAN, PlayerType::HUMAN);
	//std::cout << "SFML" << std::endl;
	// while ((pl =graphic->run()) != PlayerColor::END) {
	// 	if (pl == PlayerColor::WHITE) {
	// 		std::cout << "player White win" << std::endl;
	// 	}
	// 	else {
	// 		std::cout << "player Black win" << std::endl;

	// 	}
	// 	graphic->clear();
	// }
	return 0;
}