#ifndef	GOBANPRINTER_H
# define GOBANPRINTER_H

# include "AGraphic.hpp"
# include "Goban.hpp"

class GobanPrinter : public AGraphic
{
public:
  GobanPrinter(Goban& target);
  virtual ~GobanPrinter(void) = default;
  GobanPrinter(const GobanPrinter& other) = delete;
  GobanPrinter	&operator=(const GobanPrinter& other) = delete;

  void		print(void) const;
  void		printVictory(PlayerColor victor) const;
  void		printIllegalMove(void) const;

  void		handleInput(std::function<APlayer::Move(void)> callback);
};

#endif /* GOBANPRINTER_H */
