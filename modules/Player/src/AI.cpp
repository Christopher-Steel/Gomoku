#include "AI.hpp"

#include <iostream>

AI::AI(PlayerColor color) :
  APlayer(color, PlayerType::AI) {}

 auto		AI::getMove(void) const -> Move
{
	Move 	move;

	move.x = _x;
	move.y = _y;
	return (move);
}

void 		AI::go(Goban const &go)
{
	int 	 i = -1;
	PlayerColor player = PlayerColor::WHITE;
	PlayerColor win = PlayerColor::NONE;
	unsigned x;
	unsigned y;
	unsigned posX;
	unsigned posY;
	int score;
	int tmp[19][19];

	while (++i < 19)
	  memset(tmp[i], 0, 19);
    i = 0;
    while (i < 100)
    {
	Goban 	goban(go);
    	posX = rand() % 19;
    	posY = rand() % 19;
    	player = PlayerColor::WHITE;
	std::cout << "AI : " << posX << " " << posY << std::endl;
    	if (not goban.setStone(player, posX, posY))
	  continue;
    	while (not goban.isGameOver())
    	{
    		x = rand() % 19;
    		y = rand() % 19;
		std::cout << "AI TEST : " << x << " " << y << std::endl;
    		if (not goban.setStone(player, x, y))
		  {
		    std::cout << "Invalid Move" << std::endl;
    			continue;
		  }
    		player = (player == PlayerColor::WHITE ? PlayerColor::BLACK : PlayerColor::WHITE);
    	}
	win = goban.isGameOver();
	if (win == PlayerColor::WHITE)
	  ++tmp[posX][posY];
	else
	  --tmp[posX][posY];
    	++i;
    }
    i = 0;
    score = -1000000;
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
    std::cout << _x << " " << _y << std::endl;
}
