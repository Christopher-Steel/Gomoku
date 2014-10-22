#ifndef	GOBAN_H
# define GOBAN_H

# include <vector>

# include "BitMask.hpp"
# include "PlayerInfo.hpp"

class GobanPrinter;

class Goban
{
public:
  static const unsigned	SIZE = 19;

  enum Flag
    {
      NONE		= 0x0000,
      TAKEN		= 0x0004,
      SOLO		= 0x0008,
      PAIR		= 0x0010,
      TRIPLE		= 0x0020,
      DOUBLE_TRIPLE	= 0x0040,
      QUAD		= 0x0080,
      PENTA		= 0x0100,
      OPEN		= 0x0200
    };

  Goban(void);
  virtual ~Goban(void) = default;
  Goban(const Goban& other) = delete;
  Goban&		operator=(const Goban& other) = delete;

  const BitMask&	operator[](unsigned index) const;

  bool			setPawn(PlayerColor player, unsigned index);
  bool			setPawn(PlayerColor player, unsigned x, unsigned y);
  PlayerColor		isGameOver(void) const;

private:

  std::vector<BitMask>	_spaces;
  PlayerColor		_winner;
  bool			_rule1;
  bool			_rule2;
};

#endif /* GOBAN_H */
