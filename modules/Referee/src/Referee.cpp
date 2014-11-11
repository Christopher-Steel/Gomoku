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

}

bool	Referee::isLegalMove(PlayerColor player, const Point& point)
{
  bool	(Referee::*checks[])(PlayerColor, const Point&) =
    {
      &Referee::_isVacant,
      &Referee::_isntDoubleTriple
    };
  bool	rc = true;

  for (auto check : checks) {
    if (not (this->*check)(player, point)) {
      rc = false;
      break;
    }
  }
  return rc;
}

bool	Referee::isCapture(unsigned index, PlayerColor player, std::vector<unsigned> &captured)
{
  unsigned		player_color_id = static_cast<unsigned>(player);
  unsigned		captured_idx;
  Point::Direction	dir;
  bool			out_of_bounds;
  bool			is_capture = false;
  Radar			r;

  std::cout << "checking for captures" << std::endl;
  for (unsigned i = 0; i < 8; ++i) {
    dir = static_cast<Point::Direction>(i);
    r = _goban[index].cdirection(dir);
    std::cout << "\tdirectional radar => length " << (unsigned)r.length << " color " << (unsigned)r.color << "(searching for " << (unsigned)player << ")" << std::endl;
    if (r.length == 2 and r.color != player and r.color != PlayerColor::NONE) {
      std::cout << "Spotted a double next to me !" << std::endl;
      captured_idx = index;
      is_capture = true;
      for (unsigned j = 0; j < 2; ++j) {
	captured_idx = Traveller::travel(captured_idx, dir, out_of_bounds);
	captured.push_back(captured_idx);
	++_captures[player_color_id];
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
  // if (not _breakableFives) {
  //   return true;
  // }
  bool			out_of_bounds;
  PlayerColor		color = _goban[index].isTaken();
  Point::Direction	direction;
  unsigned		axisLength;
  unsigned		cursor;

  assert(color != PlayerColor::NONE);
  cursor = index;
  for (unsigned i = 0; i < 5; ++i) {
    std::cout << "validating fiver : " << i << std::endl;
    for (unsigned j = 0; j < 4; ++j) {
      direction = static_cast<Point::Direction>(j);
      axisLength = _goban[cursor].axis(direction);
      std::cout << "\t direction radar => length " << (unsigned)axisLength << "(searching for " << (unsigned)color << ")" << std::endl;
      if (axisLength == 2) {
	if (not watched) {
	  _watchlist.push_back(std::make_pair(index, dir));
	}
	std::cout << "getting out" << std::endl;
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

bool	Referee::_isVacant(__attribute__((unused))PlayerColor player,
			const Point &point)
{
  return not (point.isTaken());
}

bool	Referee::_isntDoubleTriple(PlayerColor player, const Point &point)
{
  if (not _doubleTriples)
    return true;
  return true; // This line will have to be replaced with proper checks
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
