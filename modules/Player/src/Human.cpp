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
  APlayer::Move move;

  move.x = 100;
  move.y = 100;
  return (move);
}

void    Human::go(Goban const &go) {}
