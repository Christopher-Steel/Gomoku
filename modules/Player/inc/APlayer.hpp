#ifndef	APLAYER_H
# define APLAYER_H

# include "PlayerInfo.hpp"
# include "Goban.hpp"

class APlayer
{
public:

  struct Move
  {
    Move(void);
    Move(unsigned x, unsigned y);
    virtual ~Move(void) = default;
    Move(const Move& other) = default;
    Move&	operator=(const Move& other) = default;

    unsigned	x;
    unsigned	y;
  };

  APlayer(PlayerColor color, PlayerType type);
  virtual ~APlayer(void) = default;
  APlayer(const APlayer& other) = delete;
  APlayer&	operator=(const APlayer& other) = delete;

  virtual Move	getMove(void) const = 0;
  PlayerColor	getColor(void) const;
  PlayerType	getType(void) const;

  virtual void    go(Goban const &go) = 0;

protected:

  PlayerColor	_color;
  PlayerType	_type;
};

#endif /* PLAYER_H */
