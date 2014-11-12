#ifndef	REFEREE_H
# define REFEREE_H

# include <array>
# include <cstdint>
# include <vector>

# include "PlayerInfo.hpp"
# include "Point.hpp"

class Goban;

class Referee
{
public:
  Referee(Goban &goban, bool rule1 = false, bool rule2 = false);
  virtual ~Referee(void) = default;
  Referee(const Referee &other) = delete;
  Referee	&operator=(const Referee &other) = delete;

  bool		isLegalMove(PlayerColor player, unsigned index);
  bool		isCapture(unsigned index, PlayerColor player,
			  std::vector<unsigned> &captured);

  /*
  ** Checks if the index and direction given make up
  ** a five stone alignment and if the rule is active
  ** it checks for fragility. If the alignment is
  ** detected as fragile, it will be put on the referee's
  ** watchlist and false will be returned.
  */
  bool		isWinningFive(unsigned index, Point::Direction dir,
			      bool watched = false);

  /*
  ** This function should be called after every move
  ** so that the referee can check the status of the
  ** fragile fives it stored. If a fragile five is
  ** broken it will be removed from referee's watchlist
  ** or if it is no longer fragile, victory will be set
  ** inside the Goban class.
  */
  void		consult(void);

  bool		breakableFives(void) const;
  bool		doubleTriples(void) const;

  void		setBreakableFives(bool on);
  void		setDoubleTriples(bool on);

private:
  typedef std::vector<std::pair<unsigned, Point::Direction>>	t_fives;

  struct BoardSegment
  {
    unsigned		origin;
    unsigned char	length : 5; // 0-31
    unsigned char	direction : 3; // 0-7
  };

  bool		_isVacant(PlayerColor player, unsigned index);

  bool		_isntDoubleTriple(PlayerColor player, unsigned index);
  unsigned	_findOpenDoubles(PlayerColor player, unsigned index,
				 std::vector<BoardSegment> &found,
				 Point::Direction ignoreDir = Point::Direction::BOTTOMLEFT);
  unsigned	_getExtendableLength(PlayerColor player, unsigned index,
				     Point::Direction dir, bool &extended) const;

  Goban		&_goban;
  t_fives	_watchlist;
  bool		_breakableFives;
  bool		_doubleTriples;
  std::array<uint8_t, 2>	_captures;
};

#endif /* REFEREE_H */
