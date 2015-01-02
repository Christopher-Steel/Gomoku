#ifndef	AGRAPHIC_H
# define AGRAPHIC_H

# include <functional>

# include "APlayer.hpp"

class Goban;

class AGraphic
{
public:
  AGraphic(Goban& target) : _goban(target) {}
  virtual ~AGraphic(void) {};

  virtual void	print(void) const = 0;
  virtual void	printVictory(PlayerColor victor) const = 0;
  virtual void	printIllegalMove(void) const = 0;

  virtual void	handleInput(std::function<APlayer::Move(void)> callback) = 0;

protected:
  Goban		&_goban;
};

#endif /* AGRAPHIC_H */
