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
   if (isOk) return (isOk);
    //std::cout << x << " " << y-1 << std::endl;
  }
  if (y + 1 < 19)
  {
    isOk = go[x * Goban::SIZE + y + 1].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
    //std::cout << x << " " << y+1 << std::endl;
  }
  if (x - 1 >= 0)
  {
    isOk = go[(x - 1) * Goban::SIZE + y].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
    //std::cout << x-1 << " " << y << std::endl;
  }
  if (x + 1 < 19)
  {
    isOk = go[(x + 1) * Goban::SIZE + y].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
    //std::cout << x+1 << " " << y << std::endl;
  }
  if (x - 1 >= 0 && y - 1 >= 0)
  {
    isOk = go[(x - 1) * Goban::SIZE + (y - 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
    //std::cout << x-1 << " " << y-1 << std::endl;
  }
  if (x + 1 < 19 && y - 1 >= 0)
  {
    isOk = go[(x + 1) * Goban::SIZE + (y - 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
    //std::cout << x+1 << " " << y-1 << std::endl;
  }
  if (x - 1 >= 0 && y + 1 < 19)
  {
    isOk = go[(x - 1) * Goban::SIZE + (y + 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
    //std::cout << x-1 << " " << y+1 << std::endl;
  }
  if (x + 1 < 19 && y + 1 < 19)
  {
    isOk = go[(x + 1) * Goban::SIZE + (y + 1)].isTaken() == PlayerColor::NONE ? false : true;
    if (isOk) return (isOk);
    //std::cout << x+1 << " " << y+1 << std::endl;
  }
  // if (isOk)
  //   std::cout << "true" << std::endl;
  // else
  //   std::cout << "false" << std::endl;
   return isOk;
}

// goban[index].direction(DIRECTION).length -> donne la longueur d'alignement dans la direction.
// goban[index].direction(DIRECTION).color -> donne la couleur dans la direction.
// goban[index].direction(DIRECTION).open -> if true alignement ouvert, false alignement fermer donc on peux bouffer

void 		AI::chooseMove(Goban const &go)
{
// 	int 	 i = -1;
// 	PlayerColor player = PlayerColor::WHITE;
// 	PlayerColor win = PlayerColor::NONE;
// 	unsigned x;
//   unsigned tmpx;
//   unsigned tmpy;
// 	unsigned posX;
// 	unsigned posY;
// 	int score;
// 	int tmp[19][19];

//   srand(getpid() * time(NULL));
// 	for (unsigned y = 0; y < Goban::SIZE; ++y) {
//     for (x = 0; x < Goban::SIZE; ++x) {
//       tmp[y][x] = 0;
//     }
//   }
//   for (unsigned y = 0; y < Goban::SIZE; ++y) {
//    for (x = 0; x < Goban::SIZE; ++x) {
//     posX = y;
//     posY = x;
//     i = 0;
//     Goban goban(go);
//         if (!check(goban, posX, posY))
//           continue;
//     //std::cout << posX << " | " << posY << std::endl;
//     while (i < 100)
//     {
// 	 	  Goban goban(go);
//     	player = PlayerColor::WHITE;
//     	if (not goban.setStone(player, posX, posY))
// 	       continue;
//       //std::cout << posX << " | " << posY << std::endl;
//       player = PlayerColor::BLACK;
//     	while (not goban.isGameOver())
//     	{
//     		tmpx = rand() % 19;
//     		tmpy = rand() % 19;
//         //std::cout << tmpx << " [] " << tmpy << std::endl;
//     		if (goban.setStone(player, tmpx, tmpy))
// 		  {
//         //std::cout << "Illegal move" << std::endl;
//         player = (player == PlayerColor::WHITE ? PlayerColor::BLACK : PlayerColor::WHITE);
// 		  }
    		
//     	}
// 	win = goban.isGameOver();
// 	if (win == PlayerColor::WHITE)
// 	  ++tmp[posY][posX];
//   ++i;
//     }
//     //std::cout << tmp[posY][posX] << std::endl;
//   }
// }
//     i = 0;
//     score = 0;
//     Goban 	goban(go);
//     //std::cout << "TEST" << std::endl;
//    // print(goban);
//     while (i < 19)
//       {
// 	for (int j = 0; j < 19; ++j)
// 	  {
//       if (not goban.setStone(player, i, j))
//         continue;
// 	    if (tmp[j][i] > score)
// 	      {
// 		      score = tmp[j][i];
// 		      posX = i;
// 		      posY = j;
// 	      }
// 	  }
// 	++i;
//       }
//     _x = posY;
//     _y = posX;
//     std::cout << _x << " " << _y << " score = " << score << std::endl;
}
