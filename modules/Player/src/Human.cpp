#include <iostream>

#include "Human.hpp"

Human::Human(PlayerColor color) :
  APlayer(color, PlayerType::HUMAN)
{

}

auto	Human::getMove(void) const -> Move
{
  Move	move;
  char	ignored;

  std::cin >> move.x;
  std::cin >> ignored;
  std::cin >> move.y;
  return move;
}
