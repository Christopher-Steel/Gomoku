#include "Goban.hpp"

Goban::Goban(void) :
  _spaces(Goban::SIZE * Goban::SIZE, Flag::NONE),
  _winner(Player::NONE),
  _rule1(false),
  _rule2(false)
{

}

const BitMask&	Goban::operator[](unsigned index) const
{
  return _spaces[index];
}

bool		Goban::setPawn(Player player, unsigned index)
{
  _spaces[index].add(player | Flag::TAKEN);
  return true;
}

bool		Goban::setPawn(Player player, unsigned x, unsigned y)
{
  _spaces[y * Goban::SIZE + x].add(player | Flag::TAKEN);
  return true;
}

Player		Goban::isGameOver(void) const
{
  return _winner;
}
