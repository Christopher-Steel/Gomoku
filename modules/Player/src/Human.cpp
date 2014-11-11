#include <iostream>
#include <sstream>
#include <string>

#include "Human.hpp"

Human::Human(PlayerColor color) :
  APlayer(color, PlayerType::HUMAN)
{

}

auto		Human::getMove(void) const -> Move
{
  std::string		line;
  std::stringstream	ss;
  Move			move;
  char			ignored;

  std::cin >> line;
  ss << line;
  ss >> move.x;
  ss >> ignored;
  ss >> move.y;
  return move;
}
