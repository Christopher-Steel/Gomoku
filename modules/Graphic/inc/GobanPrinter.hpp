#ifndef	GOBANPRINTER_H
# define GOBANPRINTER_H

# include "Goban.hpp"

class GobanPrinter
{
public:

  GobanPrinter(Goban& target);
  virtual ~GobanPrinter(void) = default;
  GobanPrinter(const GobanPrinter& other) = delete;
  GobanPrinter&	operator=(const GobanPrinter& other) = delete;

  void		print(void) const;
  void		printVictory(PlayerColor victor) const;
  void		printIllegalMove(void) const;

  void		handleInput(std::function<APlayer::Move(void)> callback);

private:

  Goban&	_goban;
};

#endif /* GOBANPRINTER_H */
