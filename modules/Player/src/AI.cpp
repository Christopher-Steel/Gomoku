#include "AI.hpp"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>


AI::AI(PlayerColor color) :
  APlayer(color, PlayerType::AI) {}

 auto		AI::getMove(void) const -> Move
{
	Move 	move;

	move.x = _x;
	move.y = _y;
	return (move);
}

void		AI::print(Goban const &_goban)
{
  unsigned	x;

  for (x = 0; x < Goban::SIZE + 2; ++x) {
    std::cout << "@";
  }
  std::cout << std::endl;
  for (unsigned y = 0; y < Goban::SIZE; ++y) {
    std::cout << "@";
    for (x = 0; x < Goban::SIZE; ++x) {
      if (_goban[y * Goban::SIZE + x].isTaken()) {
	if (_goban[y * Goban::SIZE + x].isTaken() == PlayerColor::WHITE) {
	  std::cout << "O";
	} else {
	  std::cout << "X";
	}
      } else {
	std::cout << " ";
      }
    }
    std::cout << "@" << std::endl;
  }
  for (x = 0; x < Goban::SIZE + 2; ++x) {
    std::cout << "@";
  }
  std::cout << std::endl;
}

bool    check(Goban const &go, int x, int y)
{
  bool  isOk = false;

  if (y - 1 >= 0)
  {
    isOk = go[x * Goban::SIZE + (y - 1)].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x << " " << y-1 << std::endl;
  }
  if (y + 1 < 19)
  {
    isOk = go[x * Goban::SIZE + y + 1].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x << " " << y+1 << std::endl;
  }
  if (x - 1 >= 0)
  {
    isOk = go[(x - 1) * Goban::SIZE + y].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x-1 << " " << y << std::endl;
  }
  if (x + 1 < 19)
  {
    isOk = go[(x + 1) * Goban::SIZE + y].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x+1 << " " << y << std::endl;
  }
  if (x - 1 >= 0 && y - 1 >= 0)
  {
    isOk = go[(x - 1) * Goban::SIZE + (y - 1)].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x-1 << " " << y-1 << std::endl;
  }
  if (x + 1 < 19 && y - 1 >= 0)
  {
    isOk = go[(x + 1) * Goban::SIZE + (y - 1)].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x+1 << " " << y-1 << std::endl;
  }
  if (x - 1 >= 0 && y + 1 < 19)
  {
    isOk = go[(x - 1) * Goban::SIZE + (y + 1)].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x-1 << " " << y+1 << std::endl;
  }
  if (x + 1 < 19 && y + 1 < 19)
  {
    isOk = go[(x + 1) * Goban::SIZE + (y + 1)].isTaken() == PlayerColor::NONE ? false : true;
    std::cout << x+1 << " " << y+1 << std::endl;
  }
  if (isOk)
    std::cout << "true" << std::endl;
  else
    std::cout << "false" << std::endl;
  return isOk;
}

void 		AI::go(Goban const &go)
{
	int 	 i = -1;
	PlayerColor player = PlayerColor::WHITE;
	PlayerColor win = PlayerColor::NONE;
	unsigned x;
  unsigned tmpx;
  unsigned tmpy;
	unsigned posX;
	unsigned posY;
	int score;
	int tmp[19][19];
  bool ok = false;

  srand(getpid() * time(NULL));
	for (unsigned y = 0; y < Goban::SIZE; ++y) {
    for (x = 0; x < Goban::SIZE; ++x) {
      tmp[y][x] = 0;
    }
  }
  for (unsigned y = 0; y < Goban::SIZE; ++y) {
   for (x = 0; x < Goban::SIZE; ++x) {
    posX = y;
    posY = x;
    i = 0;
    ok = false;
    Goban goban(go);
      if (!ok) {
        if (!check(goban, posX, posY))
        {
          continue;
        }
        ok = true;
      }
    //std::cout << posX << " | " << posY << std::endl;
    while (i < 300)
    {
	 	  Goban goban(go);
      if (!ok) {
        if (!check(goban, posX, posY))
        {
          break;
        }
        ok = true;
      }
    	player = PlayerColor::WHITE;
    	if (not goban.setStone(player, posX, posY))
	       break;
      player = PlayerColor::BLACK;
    	while (not goban.isGameOver())
    	{
    		tmpx = rand() % 19;
    		tmpy = rand() % 19;
        std::cout << posX << " | " << posY << std::endl;
        //std::cout << tmpx << " [] " << tmpy << std::endl;
    		if (goban.setStone(player, tmpx, tmpy))
		  {
        std::cout << "Illegal move" << std::endl;
        player = (player == PlayerColor::WHITE ? PlayerColor::BLACK : PlayerColor::WHITE);
		  }
    		
    	}
	win = goban.isGameOver();
	if (win == PlayerColor::WHITE)
	  ++tmp[posX][posY];
	else
	  --tmp[posX][posY];
    	++i;
    }
  }
}
    i = 0;
    score = -10000;
    Goban 	goban(go);
    while (i < 19)
      {
	for (int j = 0; j < 19; ++j)
	  {
	    if (tmp[i][j] > score && goban.setStone(player, i, j))
	      {
		score = tmp[i][j];
		posX = i;
		posY = j;
	      }
	  }
	++i;
      }
    _x = posX;
    _y = posY;
    std::cout << _x << " " << _y << " score = " << score << std::endl;
}
