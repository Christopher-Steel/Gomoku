#include "Goban.hpp"
#include "GobanPrinter.hpp"

int		main(void)
{
  Goban		goban;
  GobanPrinter	printer(goban);

  for (unsigned i = 0; i < Goban::SIZE * Goban::SIZE; ++i) {
    goban.setPawn((i % 2 ? Player::BLACK : Player::WHITE), i);
  }
  printer.print();
  return (0);
}
