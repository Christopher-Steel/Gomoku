#include "Traveller.hpp"

unsigned Traveller::travel(unsigned index, Point::Direction dir,
			   bool &out_of_bounds, unsigned distance)
{
  unsigned	(*directions[])(unsigned, bool &) =
    {
      &_travelLeft,
      &_travelTopLeft,
      &_travelTop,
      &_travelTopRight,
      &_travelRight,
      &_travelBottomRight,
      &_travelBottom,
      &_travelBottomLeft
    };

  out_of_bounds = false;
  while (distance > 0) {
    index = (directions[static_cast<unsigned>(dir)])(index, out_of_bounds);
    --distance;
  }
  return index;
}

unsigned Traveller::_travelLeft(unsigned index, bool &out_of_bounds)
{
  if (index % Goban::SIZE == 0) {
    out_of_bounds = true;
  }
  return index - 1;
}

unsigned Traveller::_travelTopLeft(unsigned index, bool &out_of_bounds)
{
  return _travelTop(_travelLeft(index, out_of_bounds), out_of_bounds);
}

unsigned Traveller::_travelTop(unsigned index, bool &out_of_bounds)
{
  if (index < Goban::SIZE) {
    out_of_bounds = true;
  }
  return index - Goban::SIZE;
}

unsigned Traveller::_travelTopRight(unsigned index, bool &out_of_bounds)
{
  return _travelTop(_travelRight(index, out_of_bounds), out_of_bounds);
}

unsigned Traveller::_travelRight(unsigned index, bool &out_of_bounds)
{
  if (index % Goban::SIZE == Goban::SIZE - 1) {
    out_of_bounds = true;
  }
  return index + 1;
}

unsigned Traveller::_travelBottomRight(unsigned index, bool &out_of_bounds)
{
  return _travelBottom(_travelRight(index, out_of_bounds), out_of_bounds);
}

unsigned Traveller::_travelBottom(unsigned index, bool &out_of_bounds)
{
  if (index > Goban::SIZE * (Goban::SIZE - 1)) {
    out_of_bounds = true;
  }
  return index + Goban::SIZE;
}

unsigned Traveller::_travelBottomLeft(unsigned index, bool &out_of_bounds)
{
  return _travelBottom(_travelLeft(index, out_of_bounds), out_of_bounds);
}
