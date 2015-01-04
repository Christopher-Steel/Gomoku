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
  	void 		print(Goban const &);
  	Move		getMove(void) const;
  	void 		chooseMove(Goban const &go);

 private:
 	unsigned 	_x;
 	unsigned 	_y;
 	bool 		_first;
};
