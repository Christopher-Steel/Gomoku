#include "AI.hpp"

#include <iostream>

AI::AI(PlayerColor color) :
  APlayer(color, PlayerType::AI) {}

 auto		AI::getMove(void) const -> Move
{
	Move 	move;

	move.x = rand() % 19;
	move.y = rand() % 19;
	std::cout << move.x << "  " << move.y << std::endl;
	return (move);
}

void 		AI::go(Goban const &go)
{
	Goban 	goban(go);
	PlayerColor player = PlayerColor::WHITE;
	unsigned x;
	unsigned posX;
	unsigned posY;
	int 	 i = 0;

    // while (i < 2)
    // {
    // 	posX = rand() % 19;
    // 	posY = rand() % 19;
    // 	player = PlayerColor::WHITE;
    // 	goban.setStone(player, posX, posY);
    // 	while (not goban.isGameOver())
    // 	{
    // 		posX = rand() % 19;
    // 		posY = rand() % 19;
    // 		//std::cout << posX << " " << posY << std::endl;
    // 		player = (player == PlayerColor::WHITE ? PlayerColor::BLACK : PlayerColor::WHITE);
    // 		if (not goban.setStone(player, posX, posY))
    // 			continue;
    // 	}
    // 	++i;
    // }
for (x = 0; x < Goban::SIZE + 2; ++x) {
    std::cout << "@";
  }
  std::cout << std::endl;
  for (unsigned y = 0; y < Goban::SIZE; ++y) {
    std::cout << "@";
    for (x = 0; x < Goban::SIZE; ++x) {
      if (goban[y * Goban::SIZE + x].isTaken()) {
	if (goban[y * Goban::SIZE + x].isTaken() == PlayerColor::WHITE) {
	  std::cout << "O";
	} else {
	  std::cout << "X";
	}
      } else {
		std::cout << " ";
      }
    }
    std::cout << "@" << std::endl;
  }
  for (x = 0; x < Goban::SIZE + 2; ++x) {
    std::cout << "@";
  }
  std::cout << std::endl;
}