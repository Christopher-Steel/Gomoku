#include "Game.hpp"

int		main(void)
{
  Game		game;

  game.run(PlayerType::HUMAN, PlayerType::HUMAN);
  return (0);
}
