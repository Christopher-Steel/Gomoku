#ifndef	GOBAN_H
# define GOBAN_H

# include <vector>

# include "PlayerInfo.hpp"
# include "Point.hpp"
# include "Referee.hpp"

class GobanPrinter;

class Goban
{
public:
  static const unsigned	SIZE = 19;

  Goban(void);
  virtual ~Goban(void) = default;
  Goban(const Goban &other) = delete;
  Goban			&operator=(const Goban &other) = delete;

  const Point&		operator[](unsigned index) const;

  /*
  ** The two following functions can fail and return false
  ** if the referee judges that the move is illegal. You should
  ** take into account any refusals, notify the player and give
  ** him the opportunity to try another move
  */
  bool			setStone(PlayerColor player, unsigned index);
  bool			setStone(PlayerColor player, unsigned x, unsigned y);

  PlayerColor		isGameOver(void) const;

private:
  void			_startPropagation(unsigned index, PlayerColor color);
  bool			_propagateInfo(unsigned index, Point::Direction dir,
				       PlayerColor color, int diff);

  void			_reversePropagation(unsigned index, PlayerColor color);
  void			_propagateDestruction(unsigned index, Point::Direction dir,
					      PlayerColor color, int diff);

  /*
  ** The reason I have set Referee as a friend class is
  ** because I believe that the Referee needing to be able
  ** to access _winner to set its value doesn't justify
  ** adding a public method to set the winner as it would
  ** permit future developers to manually set the winner
  ** from outside the game logic (for example they could
  ** create a cheat code to automatically win the game, and
  ** this is not something I want.
  **
  ** If you have any problems with the use of the friend
  ** keyword then I'll expect you to explain thoroughly to
  ** me why using friend is not good in this situation.
  ** You should do some research on the uses of the keyword
  ** before though because it's use is advocated by many
  ** developers in cases like this one where it enhances
  ** encapsulation (including Bjarne Stroustrup himself).
  */
  friend class		Referee;

  std::vector<Point>	_points;
  PlayerColor		_winner;
  Referee		_referee;
};

#endif /* GOBAN_H */
