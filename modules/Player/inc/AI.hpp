#pragma once

#include <stdlib.h>

#include "APlayer.hpp"

class  			AI : public APlayer
{
public:
	AI(PlayerColor color);
	virtual ~AI()noexcept = default;
	AI(const AI& other) = delete;
  	AI&	operator=(const AI& other) = delete;

  	Move		getMove(void) const;
  	void 		go(Goban const &go);
 private:
 	unsigned 	_x;
 	unsigned 	_y;
};