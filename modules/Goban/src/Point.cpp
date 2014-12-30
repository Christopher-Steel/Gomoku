#include <cassert>
#include <iostream>

#include "Point.hpp"

Point::Point(void)
{
  _center = PlayerColor::NONE;
  for (int i = 0; i < 8; ++i) {
    _directions[static_cast<unsigned>(i)].open = true;
  }
}

void		Point::take(PlayerColor player)
{
  _center = player;
}

void		Point::free(void)
{
  _center = PlayerColor::NONE;
}

PlayerColor	Point::isTaken(void) const
{
  return _center;
}

Radar		&Point::direction(Direction dir)
{
  assert(dir >= Direction::LEFT && dir <= Direction::BOTTOMLEFT);
  return _directions[dir];
}

const Radar	&Point::cdirection(Direction dir) const
{
  assert(dir >= Direction::LEFT && dir <= Direction::BOTTOMLEFT);
  return _directions[dir];
}

unsigned	Point::axis(Direction dir) const
{
  assert(dir >= Direction::LEFT && dir <= Direction::BOTTOMLEFT);
  const Radar	*directions[] =
    {
      &cdirection(dir),
      &cdirection(oppositeDirection(dir))
    };
  unsigned	length = 1;

  for (const Radar *direction : directions) {
    if (direction->color == _center) {
      length += direction->length;
    }
  }
  return length;
}

auto Point::oppositeDirection(Direction dir) -> Direction
{
  return static_cast<Direction>((static_cast<unsigned>(dir) + 4) % 8);
}
