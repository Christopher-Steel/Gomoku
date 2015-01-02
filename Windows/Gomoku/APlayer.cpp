#include "APlayer.hpp"

APlayer::APlayer(PlayerColor color, PlayerType type) :
  _color(color), _type(type)
{

}

PlayerColor	APlayer::getColor(void) const
{
  return _color;
}

PlayerType	APlayer::getType(void) const
{
  return _type;
}

// Move

APlayer::Move::Move(void) :
  x(0), y(0)
{

}

APlayer::Move::Move(unsigned x, unsigned y) :
  x(x), y(y)
{

}
