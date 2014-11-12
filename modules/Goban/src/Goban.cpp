#include <cassert>
#include <iostream>

#include "Goban.hpp"
#include "Traveller.hpp"

Goban::Goban(void) :
  _points(Goban::SIZE * Goban::SIZE),
  _winner(PlayerColor::NONE),
  _referee(*this, true, true)
{

}

const Point&	Goban::operator[](unsigned index) const
{
  return _points[index];
}

bool		Goban::setStone(PlayerColor player, unsigned index)
{
  bool		rc = false;

  if (index >= Goban::SIZE * Goban::SIZE) {
    return false;
  }
  if (_referee.isLegalMove(player, index)) {
    Point&			point = _points[index];
    std::vector<unsigned>	captured;
    rc = true;
    point.take(player);
    _startPropagation(index, player);
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
    r = _points[index].direction(Point::oppositeDirection(direction));
    added = 0;
    if (capture) {
      added = -r.length;
    } else {
      if (r.color == color) {
	added = r.length;
      }
      ++added;
    }
    startPoint = Traveller::travel(index, direction, out_of_bounds);
    if (not out_of_bounds) {
      _propagateInfo(startPoint, direction, color, added);
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
      _winner = color;
    }
  }
  unsigned	next;
  bool		out_of_bounds;
  bool		isOpen;

  if (_winner == PlayerColor::NONE) {
    next = Traveller::travel(index, dir, out_of_bounds);
    if (not out_of_bounds and point.isTaken() == color) {
      isOpen = not _propagateInfo(next, dir, color, diff);
      point.direction(oppositeDir).open = isOpen;
      if (point.direction(dir).color == color) {
	point.direction(dir).open = isOpen;
      }
    }
  }
  std::cout << "I'm gonna stop here because oob: " << out_of_bounds << " and pointColor: " << point.isTaken() << " and winner: " << (unsigned)_winner << std::endl;
  return (point.isTaken() != color and point.isTaken() != PlayerColor::NONE);
}
