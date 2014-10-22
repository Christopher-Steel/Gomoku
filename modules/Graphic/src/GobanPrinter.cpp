#include <iostream>

#include "GobanPrinter.hpp"

GobanPrinter::GobanPrinter(Goban& target) :
  _goban(target)
{

}

void	GobanPrinter::print(void) const
{
  unsigned x;

  for (x = 0; x < Goban::SIZE + 2; ++x) {
    std::cout << "#";
  }
  std::cout << std::endl;
  for (unsigned y = 0; y < Goban::SIZE; ++y) {
    std::cout << "#";
    for (x = 0; x < Goban::SIZE; ++x) {
      if (_goban[y * Goban::SIZE + x].has(Goban::Flag::TAKEN)) {
	if (_goban[y * Goban::SIZE + x].has(Player::WHITE)) {
	  std::cout << "O";
	} else {
	  std::cout << "X";
	}
      } else {
	std::cout << " ";
      }
    }
    std::cout << "#" << std::endl;
  }
  for (x = 0; x < Goban::SIZE + 2; ++x) {
    std::cout << "#";
  }
  std::cout << std::endl;

}
