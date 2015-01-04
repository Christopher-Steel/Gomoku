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

bool    check(Goban const &go, int y, int x)
{
  bool  isOk = false;

  if (x - 1 >= 0)
  {
    isOk = go[y * Goban::SIZE + (x - 1)].isTaken() == PlayerColor::NONE ? false : true;
   if (isOk) return (isOk);
    //std::cout << x << " " << y-1 << std::endl;
  }
  if (x + 1 < 19)
  {
    isOk = go[y * Goban::SIZE + x + 1].isTaken() != PlayerColor::BLACK ? false : true;
    if (isOk) return (isOk);
    //std::cout << x << " " << y+1 << std::endl;
  }
  if (y - 1 >= 0)
  {
    isOk = go[(y - 1) * Goban::SIZE + x].isTaken() != PlayerColor::BLACK ? false : true;
    if (isOk) return (isOk);
    //std::cout << x-1 << " " << y << std::endl;
  }
  if (y + 1 < 19)
  {
    isOk = go[(y + 1) * Goban::SIZE + x].isTaken() != PlayerColor::BLACK ? false : true;
    if (isOk) return (isOk);
    //std::cout << x+1 << " " << y << std::endl;
  }
  if (y - 1 >= 0 && x - 1 >= 0)
  {
    isOk = go[(y - 1) * Goban::SIZE + (x - 1)].isTaken() != PlayerColor::BLACK ? false : true;
    if (isOk) return (isOk);
    //std::cout << x-1 << " " << y-1 << std::endl;
  }
  if (y + 1 < 19 && x - 1 >= 0)
  {
    isOk = go[(y + 1) * Goban::SIZE + (x - 1)].isTaken() != PlayerColor::BLACK ? false : true;
    if (isOk) return (isOk);
    //std::cout << x+1 << " " << y-1 << std::endl;
  }
  if (y - 1 >= 0 && x + 1 < 19)
  {
    isOk = go[(y - 1) * Goban::SIZE + (x + 1)].isTaken() != PlayerColor::BLACK ? false : true;
    if (isOk) return (isOk);
    //std::cout << x-1 << " " << y+1 << std::endl;
  }
  if (y + 1 < 19 && x + 1 < 19)
  {
    isOk = go[(y + 1) * Goban::SIZE + (x + 1)].isTaken() != PlayerColor::BLACK ? false : true;
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
  Move  tmp;
  int   **score;
  std::vector<Move> pos;
  Goban goban(go);

  score = new int*[19];
  for (int y = 0; y < 19; ++y)
  {
    score[y] = new int[19];
  }

  for (int y = 0; y < 19; ++y)
  {
    for (int x = 0; x < 19; ++x)
    {
      score[y][x] = 0;
    }
  }

  for (int y = 0; y < 19; ++y)
  {
    for (int x = 0; x < 19; ++x)
    {
      if (!check(goban, y, x) || goban[y * Goban::SIZE + x].isTaken() != PlayerColor::NONE)
        continue;
      if (_first)
      {
        _x = x;
        _y = y;
        _first = false;
        return ; 
      }
      if (goban[y * Goban::SIZE + x].direction(Point::LEFT).length == 2 ||
          goban[y * Goban::SIZE + x].direction(Point::TOPLEFT).length == 2 ||
          goban[y * Goban::SIZE + x].direction(Point::TOP).length == 2 ||
          goban[y * Goban::SIZE + x].direction(Point::TOPRIGHT).length == 2 ||
          goban[y * Goban::SIZE + x].direction(Point::RIGHT).length == 2 ||
          goban[y * Goban::SIZE + x].direction(Point::BOTTOMRIGHT).length == 2 ||
          goban[y * Goban::SIZE + x].direction(Point::BOTTOM).length == 2 ||
          goban[y * Goban::SIZE + x].direction(Point::BOTTOMLEFT).length == 2)
      {
        tmp.x = x;
        tmp.y = y;
        pos.push_back(tmp);
      }
      if (goban[y * Goban::SIZE + x].direction(Point::LEFT).length > 2 ||
          goban[y * Goban::SIZE + x].direction(Point::TOPLEFT).length > 2 ||
          goban[y * Goban::SIZE + x].direction(Point::TOP).length > 2 ||
          goban[y * Goban::SIZE + x].direction(Point::TOPRIGHT).length > 2 ||
          goban[y * Goban::SIZE + x].direction(Point::RIGHT).length > 2 ||
          goban[y * Goban::SIZE + x].direction(Point::BOTTOMRIGHT).length > 2 ||
          goban[y * Goban::SIZE + x].direction(Point::BOTTOM).length > 2 ||
          goban[y * Goban::SIZE + x].direction(Point::BOTTOMLEFT).length > 2)
      {
        _x = x;
        _y = y;
        return;
      }
    }
  }
  int t = rand() % pos.size();
  _x = pos[t].x;
  _y = pos[t].y;
  _first = false;
  for (int y = 0; y < 19; ++y)
  {
    delete[] score[y];
  }
  delete[] score;
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
