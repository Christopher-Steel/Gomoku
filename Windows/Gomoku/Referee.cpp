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

bool	Referee::isLegalMove(PlayerColor player, unsigned index)
{
  bool	(Referee::*checks[])(PlayerColor, unsigned) =
    {
      &Referee::_isVacant,
      &Referee::_isntDoubleTriple
    };
  bool	rc = true;

  for (auto check : checks) {
    if (! (this->*check)(player, index)) {
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
    if (r.length == 2 && r.color != player && r.color != PlayerColor::NONE) {
      unsigned	other_side(Traveller::travel(index, dir, out_of_bounds, 3));
      if (! out_of_bounds && _goban[other_side].isTaken() == player) {
	captured_idx = index;
	is_capture = true;
	for (unsigned j = 0; j < 2; ++j) {
	  captured_idx = Traveller::travel(captured_idx, dir, out_of_bounds);
	  captured.push_back(captured_idx);
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
  if (! _breakableFives) {
    return true;
  }
  bool			out_of_bounds;
  Point::Direction	direction;
  unsigned		axisLength;
  unsigned		cursor;

  assert(_goban[index].isTaken() != PlayerColor::NONE);
  cursor = index;
  for (unsigned i = 0; i < 5; ++i) {
    for (unsigned j = 0; j < 4; ++j) {
      direction = static_cast<Point::Direction>(j);
      axisLength = _goban[cursor].axis(direction);
      if (axisLength == 2) {
	if (! watched) {
	  _watchlist.push_back(std::make_pair(index, dir));
	}
	return false;
      }
    }
    cursor = Traveller::travel(cursor, dir, out_of_bounds);
    assert(out_of_bounds == false);
  }
  return true;
}

void	Referee::consult(void)
{
  for (auto &fiver : _watchlist) {
    if (isWinningFive(fiver.first, fiver.second, true)) {
      _goban._winner = _goban[fiver.first].isTaken();
      break;
    }
  }
}

bool	Referee::_isVacant(PlayerColor player,
			   unsigned index)
{
	(void)player;
  return ! (_goban[index].isTaken());
}

bool	Referee::_isntDoubleTriple(PlayerColor player, unsigned index)
{
  bool	rc = true;
  if (! _doubleTriples)
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
      while (rc && i <= seg.length && ! out_of_bounds) {
	std::vector<BoardSegment>	segments;

      	if (_findOpenDoubles(player, cursor, segments,
			     Point::oppositeDirection(dir)) > 0) {
	  rc = false;
	  break;
	}
	cursor = Traveller::travel(cursor, dir, out_of_bounds);
	++i;
      }
      if (! rc) {
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
    if (len >= 2 && r.cdirection(dir).open && r.cdirection(direction).open) {
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
  if (r.color == PlayerColor::NONE && ! extended) {
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
