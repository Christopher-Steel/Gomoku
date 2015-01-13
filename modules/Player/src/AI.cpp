#include "AI.hpp"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>


AI::AI(PlayerColor color) :
  APlayer(color, PlayerType::AI) {_first = true;}

 auto		AI::getMove(void) const -> Move
{
	Move 	move;

	move.x = _x;
	move.y = _y;
	return (move);
}

bool    AI::check(Goban const &go, int y, int x)
{
  bool  isOk = false;

  if (x - 1 >= 0)
  {
    isOk = go[y * Goban::SIZE + (x - 1)].isTaken() == PlayerColor::NONE ? false : true;
   if (isOk) return (isOk);
  }
  if (x + 1 < 19)
  {
    isOk = go[y * Goban::SIZE + x + 1].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
  }
  if (y - 1 >= 0)
  {
    isOk = go[(y - 1) * Goban::SIZE + x].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
  }
  if (y + 1 < 19)
  {
    isOk = go[(y + 1) * Goban::SIZE + x].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
  }
  if (y - 1 >= 0 && x - 1 >= 0)
  {
    isOk = go[(y - 1) * Goban::SIZE + (x - 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
  }
  if (y + 1 < 19 && x - 1 >= 0)
  {
    isOk = go[(y + 1) * Goban::SIZE + (x - 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
  }
  if (y - 1 >= 0 && x + 1 < 19)
  {
    isOk = go[(y - 1) * Goban::SIZE + (x + 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
  }
  if (y + 1 < 19 && x + 1 < 19)
  {
    isOk = go[(y + 1) * Goban::SIZE + (x + 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
  }
   return isOk;
}

bool    AI::checkEat(Goban const &go, int x, int y)
{
  if (x - 3 >= 0)
  {
    if (go[y * Goban::SIZE + (x - 1)].isTaken() == PlayerColor::BLACK && go[y * Goban::SIZE + (x - 2)].isTaken() == PlayerColor::BLACK
        && go[y * Goban::SIZE + (x - 3)].isTaken() == PlayerColor::WHITE)
      return (true);
  }
  if (x + 3 < 19)
  {
    if (go[y * Goban::SIZE + (x + 1)].isTaken() == PlayerColor::BLACK && go[y * Goban::SIZE + (x + 2)].isTaken() == PlayerColor::BLACK
        && go[y * Goban::SIZE + (x + 3)].isTaken() == PlayerColor::WHITE)
      return (true);
  }
  if (y - 3 >= 0)
  {
    if (go[(y - 1) * Goban::SIZE + x].isTaken() == PlayerColor::BLACK && go[(y - 2) * Goban::SIZE + x].isTaken() == PlayerColor::BLACK
        && go[(y - 3) * Goban::SIZE + x].isTaken() == PlayerColor::WHITE)
      return (true);
  }
  if (y + 3 < 19)
  {
    if (go[(y + 1) * Goban::SIZE + x].isTaken() == PlayerColor::BLACK && go[(y + 2) * Goban::SIZE + x].isTaken() == PlayerColor::BLACK
        && go[(y + 3) * Goban::SIZE + x].isTaken() == PlayerColor::WHITE)
      return (true);
  }
  if (y - 3 >= 0 && x - 3 >= 0)
  {
    if (go[(y - 1) * Goban::SIZE + (x - 1)].isTaken() == PlayerColor::BLACK && go[(y - 2) * Goban::SIZE + (x - 2)].isTaken() == PlayerColor::BLACK
        && go[(y - 3) * Goban::SIZE + (x - 3)].isTaken() == PlayerColor::WHITE)
      return (true);
  }
  if (y + 3 < 19 && x - 3 >= 0)
  {
    if (go[(y + 1) * Goban::SIZE + (x - 1)].isTaken() == PlayerColor::BLACK && go[(y + 2) * Goban::SIZE + (x - 2)].isTaken() == PlayerColor::BLACK
        && go[(y + 3) * Goban::SIZE + (x - 3)].isTaken() == PlayerColor::WHITE)
      return (true);
  }
  if (y - 3 >= 0 && x + 3 < 19)
  {
    if (go[(y - 1) * Goban::SIZE + (x + 1)].isTaken() == PlayerColor::BLACK && go[(y - 2) * Goban::SIZE + (x + 2)].isTaken() == PlayerColor::BLACK
        && go[(y - 3) * Goban::SIZE + (x + 3)].isTaken() == PlayerColor::WHITE)
      return (true);
  }
  if (y + 3 < 19 && x + 3 < 19)
  {
    if (go[(y + 1) * Goban::SIZE + (x + 1)].isTaken() == PlayerColor::BLACK && go[(y + 2) * Goban::SIZE + (x + 2)].isTaken() == PlayerColor::BLACK
        && go[(y + 3) * Goban::SIZE + (x + 3)].isTaken() == PlayerColor::WHITE)
        return (true);
  }
   return false; 
}

// goban[index].direction(Direction).length -> donne la longueur d'alignement dans la direction.
// goban[index].direction(Direction).color -> donne la couleur dans la direction.
// goban[index].direction(Direction).open -> if true alignement ouvert, false alignement fermer donc on peux bouffer

bool    AI::checkWinAI(Goban &goban, int x, int y)
{
  if (goban[y * Goban::SIZE + x].direction(Point::Direction::LEFT).length > 3 ||
          goban[y * Goban::SIZE + x].direction(Point::Direction::TOPLEFT).length > 3 ||
          goban[y * Goban::SIZE + x].direction(Point::Direction::TOP).length > 3 ||
          goban[y * Goban::SIZE + x].direction(Point::Direction::TOPRIGHT).length > 3 ||
          goban[y * Goban::SIZE + x].direction(Point::Direction::RIGHT).length > 3 ||
          goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMRIGHT).length > 3 ||
          goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOM).length > 3 ||
          goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMLEFT).length > 3)
      return (true);
  return (false);
}

bool    AI::checkAlign(Goban &goban, int x, int y, PlayerColor color)
{
  if ((goban[y * Goban::SIZE + x].direction(Point::Direction::LEFT).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::LEFT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::TOPLEFT).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::TOPLEFT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::TOP).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::TOP).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::TOPRIGHT).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::TOPRIGHT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::RIGHT).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::RIGHT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMRIGHT).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMRIGHT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOM).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOM).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMLEFT).length == 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMLEFT).color == color))
      return (true);
  return (false);
}

bool    AI::checkAlignWin(Goban &goban, int x, int y, PlayerColor color)
{
  if ((goban[y * Goban::SIZE + x].direction(Point::Direction::LEFT).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::LEFT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::TOPLEFT).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::TOPLEFT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::TOP).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::TOP).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::TOPRIGHT).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::TOPRIGHT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::RIGHT).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::RIGHT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMRIGHT).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMRIGHT).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOM).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOM).color == color) ||
      (goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMLEFT).length > 2 && goban[y * Goban::SIZE + x].direction(Point::Direction::BOTTOMLEFT).color == color))
      return (true);
  return (false);
}

void 		AI::chooseMove(Goban const &go)
{
  Move		tmp;
  int		**score;
  std::vector<Move> pos;
  Goban		goban(go);
  bool		nothing;
  PlayerColor	player = PlayerColor::WHITE;
  PlayerColor	win = PlayerColor::NONE;
  int		x;
  int		y;

  score = new int*[19];
  for (int y = 0; y < 19; ++y)
  {
    score[y] = new int[19];
  }

  for (int y = 0; y < 19; ++y)
  {
    for (int x = 0; x < 19; ++x)
    {
      score[y][x] = -1;
    }
  }

  for (int y = 0; y < 19; ++y)
  {
    for (int x = 0; x < 19; ++x)
    {
      nothing = false;
      if (goban[y * Goban::SIZE + x].isTaken() != PlayerColor::NONE || !check(goban, y, x))
        continue;
      if (_first)
      {
        _x = x;
        _y = y;
        _first = false;
        return ; 
      }
      if (checkWinAI(goban, x, y))
	    {
	      _x = x;
	      _y = y;
	      return; 
	    }
      if (checkAlign(goban, x, y, PlayerColor::BLACK))
      {
        tmp.x = x;
        tmp.y = y;
        pos.push_back(tmp);
        nothing = true;
        score[y][x] += 10;
      }
      if (checkAlign(goban, x, y, PlayerColor::WHITE))
      {
        tmp.x = x;
        tmp.y = y;
        pos.push_back(tmp);
        nothing = true;
        score[y][x] += 30;
      }
      if (checkAlignWin(goban, x, y, PlayerColor::BLACK))
	    {
        tmp.x = x;
        tmp.y = y;
        pos.push_back(tmp);
        nothing = true;
        score[y][x] += 100;
	    }
      if (checkAlignWin(goban, x, y, PlayerColor::WHITE))
	    {
	      tmp.x = x;
	      tmp.y = y;
	      pos.push_back(tmp);
	      nothing = true;
        score[y][x] += 70;
	    }
      if (checkEat(goban, x, y))
      {
        std::cout << "Eat" << x << y << std::endl;
        tmp.x = x;
        tmp.y = y;
        pos.push_back(tmp);
        nothing = true;
        score[y][x] += 45; 
      }
      if (!nothing)
	    {
          tmp.x = x;
          tmp.y = y;
          pos.push_back(tmp);
	    }
    }
  }

  int		tmpX = 0;
  int		tmpY = 0;
  for (unsigned int i=0; i < pos.size(); ++i)
    {
      x = pos[i].x;
      y = pos[i].y;
      ++score[y][x];
      for (int j = 0; j < 100; ++j)
	{
	  Goban gob(go);
	  player = PlayerColor::WHITE;
	  if (not gob.setStone(player, x, y))
	    continue;
	  player = PlayerColor::BLACK;
	  while (not gob.isGameOver())
	    {
	      tmpX = rand() % 19;
	      tmpY = rand() % 19;
	      if (not gob.setStone(player, tmpX, tmpY))
		continue;
	      player = (player == PlayerColor::WHITE ? PlayerColor::BLACK : PlayerColor::WHITE);
	    }
	  win = gob.isGameOver();
	  if (win == PlayerColor::WHITE)
	    ++score[y][x];
	}
    }
  int		res = -1;
  Goban		gob(go);
  for (int y = 0; y < 19; ++y)
    {
      for (int x = 0; x < 19; ++x)
	    {
	       if (score[y][x] > -1 && score[y][x] > res && gob.setStone(PlayerColor::WHITE, x, y))
	       {
            res = score[y][x]; 
	          tmpX = x;
	          tmpY = y;
	       }
	    }
    }
  _x = tmpX;
  _y = tmpY;
  std::cout << "score = " << score[_y][_x] << std::endl;
  _first = false;
  for (int y = 0; y < 19; ++y)
  {
    delete[] score[y];
  }
  delete[] score;
}
