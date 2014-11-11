#include <cassert>
#include <iostream>

#include "Goban.hpp"
#include "Traveller.hpp"

Goban::Goban(void) :
  _points(Goban::SIZE * Goban::SIZE),
  _winner(PlayerColor::NONE),
  _referee(*this)
{

}

const Point&	Goban::operator[](unsigned index) const
{
  return _points[index];
}

bool		Goban::setStone(PlayerColor player, unsigned index)
{
  if (index >= Goban::SIZE * Goban::SIZE) {
    return false;
  }

  Point&	point = _points[index];
  bool		rc = false;

  if (_referee.isLegalMove(player, point)) {
    rc = true;
    point.take(player);
    _startPropagation(index, player);
    std::vector<unsigned>	captured;

    if (_referee.isCapture(index, player, captured)) {
      for (auto capture : captured) {
	_points[capture].free();
	_startPropagation(capture, _points[index].isTaken(), true);
      }
    }
  }
  _referee.consult();
  return rc;
}

bool		Goban::setStone(PlayerColor player, unsigned x, unsigned y)
{
  return this->setStone(player, y * Goban::SIZE + x);
}

PlayerColor	Goban::isGameOver(void) const
{
  return _winner;
}

void		Goban::_startPropagation(unsigned index, PlayerColor color, bool capture)
{
  Point::Direction	direction;
  int			added;
  unsigned		startPoint;
  bool			out_of_bounds;
  Radar			r;

  for (unsigned dir = 0; dir < 8; ++dir) {
    direction = static_cast<Point::Direction>(dir);
    std::cout << "Travelling in direction " << (unsigned)direction << std::endl;
    r = _points[index].direction(Point::oppositeDirection(direction));
    added = 0;
    if (capture) {
      std::cout << "Capturing a diff of " << added * -1 << std::endl;
      added = -r.length;
    } else {
      if (r.color == color) {
	added = r.length;
      }
      ++added;
    }
    startPoint = Traveller::travel(index, direction, out_of_bounds);
    if (out_of_bounds) {
      std::cout << "Nope, not going there, that's off the grid." << std::endl;
    }
    if (not out_of_bounds and _propagateInfo(startPoint, direction, color, added) == true) {
      _winner = color;
      break ;
    }
  }
}

bool		Goban::_propagateInfo(unsigned index, Point::Direction dir,
				      PlayerColor color, int diff)
{
  assert(index < Goban::SIZE * Goban::SIZE);
  Point&		point = _points[index];
  Point::Direction	oppositeDir = Point::oppositeDirection(dir);

  std::cout << "PING index : " << index
	    << " taken : " << (unsigned)point.isTaken()
	    << " set " << (unsigned)oppositeDir
	    << " to " << point.direction(oppositeDir).length + diff << std::endl;
  point.direction(oppositeDir).color = color;
  point.direction(oppositeDir).length += diff;
  if (point.direction(oppositeDir).length == 4 and point.isTaken() == color) {
    std::cout << "Looks like i found a fiver" << std::endl;
    if (_referee.isWinningFive(index, oppositeDir)) {
      std::cout << "A winning fiver !" << std::endl;
      return true;
    }
  }
  unsigned	next;
  bool		out_of_bounds;

  next = Traveller::travel(index, dir, out_of_bounds);
  if (not out_of_bounds and point.isTaken() == color) {
    return _propagateInfo(next, dir, color, diff);
  }
  std::cout << "I'm gonna stop here because oob: " << out_of_bounds << " and pointColor: " << point.isTaken() << std::endl;
  return false;
}
