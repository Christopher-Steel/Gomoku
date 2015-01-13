#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

#include "Goban.hpp"
#include "Referee.hpp"
#include "Traveller.hpp"

Referee::Referee(Goban &goban, bool rule1, bool rule2) :
  _goban(goban),
  _breakableFives(rule1),
  _doubleTriples(rule2)
{
  _captures[0] = 0;
  _captures[1] = 0;
}

Referee::Referee(const Referee &other) : _goban(other._goban)
{
  _watchlist = other._watchlist;
  _breakableFives = other._breakableFives;
  _doubleTriples = other._doubleTriples;
  _captures = other._captures;
}

Referee &Referee::operator=(const Referee &other)
{
  _goban = other._goban;
  _watchlist = other._watchlist;
  _breakableFives = other._breakableFives;
  _doubleTriples = other._doubleTriples;
  _captures = other._captures;
  return (*this);
}

bool	Referee::isLegalMove(PlayerColor player, unsigned index)
{
  bool	(Referee::*checks[])(PlayerColor, unsigned) =
    {
      &Referee::_isVacant,
      &Referee::_isntDoubleTriple
    };
  bool	rc = true;

  for (auto check : checks) {
    if (not (this->*check)(player, index)) {
      rc = false;
      break;
    }
  }
  return rc;
}

bool	Referee::isCapture(unsigned index, PlayerColor player, std::vector<unsigned> &captured)
{
  unsigned		player_color_id = static_cast<unsigned>(player) - 1;
  unsigned		captured_idx;
  Point::Direction	dir;
  bool			out_of_bounds;
  bool			is_capture = false;
  Radar			r;

  for (unsigned i = 0; i < 8; ++i) {
    dir = static_cast<Point::Direction>(i);
    r = _goban[index].cdirection(dir);
    if (r.length == 2 and r.color != player and r.color != PlayerColor::NONE) {
      unsigned	other_side(Traveller::travel(index, dir, out_of_bounds, 3));
      if (not out_of_bounds and _goban[other_side].isTaken() == player) {
	captured_idx = index;
	is_capture = true;
	for (unsigned j = 0; j < 2; ++j) {
	  captured_idx = Traveller::travel(captured_idx, dir, out_of_bounds);
	  captured.push_back(captured_idx);
	  _goban.setCapture(captured_idx);
	  ++_captures[player_color_id];
	}
      }
    }
  }
  if (_captures[player_color_id] >= 10) {
    _goban._winner = player;
  }
  return is_capture;
}

bool	Referee::isWinningFive(unsigned index, Point::Direction dir, bool watched)
{
  if (not _breakableFives) {
    return true;
  }
  bool			out_of_bounds;
  Point::Direction	oppositeDir = Point::oppositeDirection(dir);
  Point::Direction	direction = static_cast<Point::Direction>(0);
  unsigned		length;
  unsigned		cursor;

  assert(_goban[index].isTaken() != PlayerColor::NONE);
  cursor = index;
  for (unsigned i = 0; i < 5; ++i) {
    for (unsigned j = 0; j < 8; ++j) {
      if (direction == dir or direction == oppositeDir) {
	std::cout << "TOTOTOTO" << std::endl;
	direction = static_cast<Point::Direction>(j);
	length = _goban[cursor].direction(direction).length;
	if (length == 2) {
	  if (not Goban::isBorderPoint(cursor)
	      and not Goban::isBorderPoint(Traveller::travel(cursor, direction, out_of_bounds))) {
	    std::cout << "DIRECTION " << direction << " POS " << cursor % 19 << "/" << cursor / 19 << " oob " << out_of_bounds << std::endl;
	    if (not watched
		and /*((_goban[cursor].cdirection(direction).open == true)
		      xor (_goban[cursor].cdirection(Point::oppositeDirection(direction)).open == true))*/ true) {
	      _watchlist.push_back(std::make_tuple(index, dir, true));
	      return false;
	    } else {
	      return true;
	    }
	  }
	}
      }
    }
    cursor = Traveller::travel(cursor, dir, out_of_bounds);
    assert(out_of_bounds == false);
  }
  return true;
}

void	Referee::consult(void)
{
  unsigned		cursor;
  Point::Direction	direction;
  bool			firstTurn;

  _watchlist.erase(std::remove_if(_watchlist.begin(), _watchlist.end(),
				  [this](t_fiver &fiver) {
    unsigned		cursor;
    Point::Direction	direction;
    bool		firstTurn;
    unsigned		i;
    bool		out_of_bounds;

    std::tie(cursor, direction, firstTurn) = fiver;
    for (i = 0; i < 5; ++i) {
      if (not _goban[cursor].isTaken()) {
	//std::cout << "broken fiver !" << std::endl;
	return true;
      }
      cursor = Traveller::travel(cursor, direction, out_of_bounds, 1);
      assert(out_of_bounds == false);
    }
    return false;
  }), _watchlist.end());
  for (auto &fiver : _watchlist) {
    std::tie(cursor, direction, firstTurn) = fiver;
    if (not firstTurn and isWinningFive(cursor, direction, true)) {
      //std::cout << "checking fiver" << std::endl;
      _goban._winner = _goban[cursor].isTaken();
      break;
    }
    std::get<2>(fiver) = false;
    //std::cout << "fiver protection : " << std::get<2>(fiver) << std::endl;

  }
}

bool	Referee::_isVacant(__attribute__ ((unused))PlayerColor player,
			   unsigned index)
{
  return not (_goban[index].isTaken());
}

bool	Referee::_isntDoubleTriple(PlayerColor player, unsigned index)
{
  bool	rc = true;
  if (not _doubleTriples)
    return rc;
  std::vector<BoardSegment>	found;
  unsigned			doubles;
  unsigned			cursor;
  int				i;
  bool				out_of_bounds = false;
  Point::Direction		dir;

  doubles = _findOpenDoubles(player, index, found);
  if (doubles != 1) {
    rc = (doubles == 0);
  } else {
    for (BoardSegment &seg : found) {
      cursor = seg.origin;
      i = 0;
      dir = static_cast<Point::Direction>(seg.direction);
      while (rc and i <= seg.length and not out_of_bounds) {
	std::vector<BoardSegment>	segments;

      	if (_findOpenDoubles(player, cursor, segments,
			     Point::oppositeDirection(dir)) > 0) {
	  rc = false;
	  break;
	}
	cursor = Traveller::travel(cursor, dir, out_of_bounds);
	++i;
      }
      if (not rc) {
	break;
      }
    }
  }
  return rc;
}

unsigned	Referee::_findOpenDoubles(PlayerColor player, unsigned index,
					  std::vector<BoardSegment> &found,
					  Point::Direction ignoreDir)
{
  Point::Direction	dir;
  bool			out_of_bounds;
  bool			extended;
  unsigned		origin;
  unsigned char		len;
  Point::Direction	direction;

  for (unsigned i = 0; i < 4; ++i) {
    extended = false;
    dir = static_cast<Point::Direction>(i);
    if (dir == ignoreDir) {
      continue;
    }
    direction = Point::oppositeDirection(dir);
    len = _getExtendableLength(player, index, dir, extended);
    origin = Traveller::travel(index, dir, out_of_bounds, len + (extended ? 1 : 0));
    len += _getExtendableLength(player, index, Point::oppositeDirection(dir), extended);
    const Point	&r = _goban[index];
    if (len >= 2 /*and r.cdirection(dir).open and r.cdirection(direction).open*/) {
      len += (extended ? 1 : 0);
      found.push_back({origin, len, direction});
    }
  }
  return found.size();
}

unsigned	Referee::_getExtendableLength(PlayerColor player, unsigned index,
					      Point::Direction dir, bool &extended) const
{
  Radar		r;
  unsigned	len = 0;
  unsigned	cursor;
  bool		out_of_bounds;
  bool		tried_extend = false;

  cursor = index;
  r = _goban[cursor].cdirection(dir);
  if (r.color == player) {
    len = r.length;
    cursor = Traveller::travel(cursor, dir, out_of_bounds, len);
    if (out_of_bounds) {
      return 0;
    }
    r = _goban[cursor].cdirection(dir);
  }
  if (r.color == PlayerColor::NONE and not extended) {
    tried_extend = true;
    cursor = Traveller::travel(cursor, dir, out_of_bounds);
    if (out_of_bounds) {
      return len;
    }
    r = _goban[cursor].cdirection(dir);
  }
  if (r.color != player) {
    return len;
  }
  if (tried_extend) {
    extended = true;
  }
  return r.length + len;
}

/*
** Accessors (nothing interesting past here)
*/
bool	Referee::breakableFives(void) const
{
  return _breakableFives;
}

bool	Referee::doubleTriples(void) const
{
  return _doubleTriples;
}

void	Referee::setBreakableFives(bool on)
{
  _breakableFives = on;
}

void	Referee::setDoubleTriples(bool on)
{
  _doubleTriples = on;
}
