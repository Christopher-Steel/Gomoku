#pragma once

#include <stdlib.h>
#include <string.h>
#include <vector>

#include "APlayer.hpp"

class  			AI : public APlayer
{
public:
	AI(PlayerColor color);
	virtual ~AI()noexcept = default;
	AI(const AI& other) = delete;
  	AI&	operator=(const AI& other) = delete;
  	Move		getMove(void) const;
  	void 		chooseMove(Goban const &go);
 
 private:
 	bool 		check(Goban const &, int, int);
 	bool 		checkEat(Goban const &, int, int);
 	bool 		checkWinAI(Goban &, int, int);
 	bool 		checkAlign(Goban &, int, int, PlayerColor);
 	bool		checkAlignWin(Goban &, int, int, PlayerColor);
 	unsigned 	_x;
 	unsigned 	_y;
 	bool 		_first;
};
