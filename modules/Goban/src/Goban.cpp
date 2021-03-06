#include <cassert>
#include <iostream>

#include "Goban.hpp"
#include "Traveller.hpp"

Goban::Goban(void) :
  _points(Goban::SIZE * Goban::SIZE),
  _freePoints(Goban::SIZE * Goban::SIZE),
  _winner(PlayerColor::NONE),
  _referee(*this, true, true)
{
  bool			out_of_bounds;
  Point::Direction	dir;

  for (unsigned y = 0; y < Goban::SIZE; ++y) {
    for (unsigned x = 0; x < Goban::SIZE; ++x) {
      if (y == 0 || x == 0 || y == Goban::SIZE - 1 || x == Goban::SIZE - 1) {
	for (int i = 0; i < 8; ++i) {
	  dir = static_cast<Point::Direction>(i);
	  Traveller::travel(y * Goban::SIZE + x, dir, out_of_bounds, 1);
	  if (out_of_bounds)
	    _points[y * Goban::SIZE + x].direction(dir).open = false;
	}
      }
    }
  }
}

Goban::Goban(const Goban &other) :
  _captured(other._captured),
  _points(other._points),
  _freePoints(other._freePoints),
  _winner(other._winner),
  _referee(*this, other._referee.breakableFives(), true)
{

}

Goban     &Goban::operator=(const Goban &other)
{
  _points = other._points;
  _referee = {*this, other._referee.breakableFives(), other._referee.doubleTriples()};
  _captured = other._captured;
  _freePoints = other._freePoints;
  _winner = other._winner;
  return *this;
}

const Point&		Goban::operator[](unsigned index) const
{
  return _points[index];
}

Point&  Goban::operator[](unsigned index)
{
  return _points[index];
}

bool			Goban::setStone(PlayerColor player, unsigned index)
{
  bool		rc = false;

  if (index >= Goban::SIZE * Goban::SIZE) {
    return false;
  }
  if (_referee.isLegalMove(player, index)) {
    Point&			point = _points[index];
    std::vector<unsigned>	captured;
    PlayerColor			target;

    rc = true;
    point.take(player);
    _startPropagation(index, player);
    --_freePoints;
    if (_referee.isCapture(index, player, captured)) {
      for (auto capture : captured) {
      	target = _points[capture].isTaken();
      	_points[capture].free();
      	_reversePropagation(capture, target);
	++_freePoints;
      }
    }
    _referee.consult();
  }
  return rc;
}

bool			Goban::setStone(PlayerColor player, unsigned x, unsigned y)
{
  return this->setStone(player, y * Goban::SIZE + x);
}

void			Goban::setCapture(unsigned pionToCapture)
{
  _captured.push_back(pionToCapture);
}

PlayerColor		Goban::isGameOver(void) const
{
  if (_freePoints == 0) {
    return PlayerColor::FULL;
  }
  return _winner;
}

std::list<unsigned>	&Goban::getCapture()
{
  return _captured;
}

bool			Goban::isBorderPoint(unsigned index)
{
  Point::Direction	directions[] =
    {
      Point::Direction::LEFT,
      Point::Direction::TOP,
      Point::Direction::RIGHT,
      Point::Direction::BOTTOM
    };
  unsigned	nbDirs = sizeof(directions) / sizeof(*directions);
  bool		out_of_bounds;

  for (unsigned dir = 0; dir < nbDirs; ++dir) {
    Traveller::travel(index, directions[dir], out_of_bounds, 1);
    if (out_of_bounds) {
      return true;
    }
  }
  return false;
}

void		Goban::_startPropagation(unsigned index, PlayerColor color)
{
  Point::Direction	direction;
  int			added;
  unsigned		startPoint;
  bool			out_of_bounds;
  Radar			r;
  bool			oldOpen;

  for (unsigned dir = 0; dir < 8; ++dir) {
    direction = static_cast<Point::Direction>(dir);
    r = _points[index].direction(Point::oppositeDirection(direction));
    added = 1;
    if (r.color == color) {
      oldOpen = r.open;
      added += r.length;
    } else if (r.color == PlayerColor::NONE) {
      oldOpen = true;
    } else {
      oldOpen = false;
    }
    startPoint = Traveller::travel(index, direction, out_of_bounds);
    if (not out_of_bounds) {
      _propagateInfo(startPoint, direction, color, added, oldOpen);
    }
  }
}

bool		Goban::_propagateInfo(unsigned index, Point::Direction dir,
				      PlayerColor color, int diff, bool oldOpen)
{
  assert(index < Goban::SIZE * Goban::SIZE);
  Point			&point = _points[index];
  Point::Direction	oppositeDir = Point::oppositeDirection(dir);
  unsigned		next;
  bool			out_of_bounds;
  bool			isOpen;

  point.direction(oppositeDir).color = color;
  point.direction(oppositeDir).length += diff;
  if (point.direction(oppositeDir).length == 4 and point.isTaken() == color) {
    if (_referee.isWinningFive(index, oppositeDir)) {
      _winner = color;
    }
  }

  if (_winner == PlayerColor::NONE) {
    next = Traveller::travel(index, dir, out_of_bounds);
    point.direction(oppositeDir).open = oldOpen;
    if (not out_of_bounds) {
      if (point.isTaken() == color) {
	isOpen = _propagateInfo(next, dir, color, diff, oldOpen);
	if (point.direction(dir).color == color
	    || point.direction(dir).color == PlayerColor::NONE) {
	  point.direction(dir).open = isOpen;
	}
      } else if (point.isTaken() != PlayerColor::NONE) {
	_propagateOpenness(next, dir, point.isTaken(), false);
      }
    }
  }
  return (point.isTaken() != color and point.isTaken() != PlayerColor::NONE);
}

void		Goban::_propagateOpenness(unsigned index, Point::Direction dir, PlayerColor color, bool isOpen)
{
  Point			&point = _points[index];
  Point::Direction	oppositeDir = Point::oppositeDirection(dir);
  unsigned		next;
  bool			out_of_bounds;

  point.direction(oppositeDir).open = isOpen;
  next = Traveller::travel(index, dir, out_of_bounds);
  if (not out_of_bounds and point.isTaken() == color) {
    _propagateOpenness(next, dir, color, isOpen);
  }
}

void		Goban::_reversePropagation(unsigned index, PlayerColor color)
{
  Point::Direction	direction;
  int			removed;
  unsigned		startPoint;
  bool			out_of_bounds;
  Radar			r;

  for (unsigned dir = 0; dir < 8; ++dir) {
    direction = static_cast<Point::Direction>(dir);
    r = _points[index].direction(Point::oppositeDirection(direction));
    removed = 1;
    if (r.color == color) {
      removed += r.length;
    }
    startPoint = Traveller::travel(index, direction, out_of_bounds);
    if (not out_of_bounds) {
      _propagateDestruction(startPoint, direction, color, removed);
    }
  }
}

void		Goban::_propagateDestruction(unsigned index, Point::Direction dir,
					     PlayerColor color, int diff)
{
  assert(index < Goban::SIZE * Goban::SIZE);
  Point::Direction	oppositeDir(Point::oppositeDirection(dir));
  Radar			&r = _points[index].direction(oppositeDir);
  bool			out_of_bounds;
  unsigned		next;
  PlayerColor		pointColor;

  r.length -= diff;
  if (r.length == 0) {
    r.color = PlayerColor::NONE;
  }
  r.open = true;
  next = Traveller::travel(index, dir, out_of_bounds);
  if (not out_of_bounds) {
    if ((pointColor = _points[index].isTaken()) == color) {
      _propagateDestruction(next, dir, color, diff);
    } else if (pointColor != PlayerColor::NONE) {
      _propagateOpenness(next, dir, pointColor, true);
    }
  }
}
