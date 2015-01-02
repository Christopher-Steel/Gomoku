#include <iostream>
#include <string>

#include "GobanPrinter.hpp"

GobanPrinter::GobanPrinter(Goban& target) :
  AGraphic(target)
{

}

void		GobanPrinter::print(void) const
{
  unsigned	x;

  for (x = 0; x < Goban::SIZE + 2; ++x) {
    std::cout << "#";
  }
  std::cout << std::endl;
  for (unsigned y = 0; y < Goban::SIZE; ++y) {
    std::cout << "#";
    for (x = 0; x < Goban::SIZE; ++x) {
      if (_goban[y * Goban::SIZE + x].isTaken()) {
	if (_goban[y * Goban::SIZE + x].isTaken() == PlayerColor::WHITE) {
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

void		GobanPrinter::printVictory(PlayerColor victor) const
{
  std::string	messages[] =
    {
      "Hey ! Nobody won !",
      "Congratulations white player, you win !",
      "Congratulations black player, you win !"
    };

  std::cout << "End of game : " << messages[static_cast<unsigned>(victor)] << std::endl;
}

void		GobanPrinter::printIllegalMove(void) const
{
  std::cout << "Illegal move ! try again..." << std::endl;
}

void		GobanPrinter::handleInput(std::function<APlayer::Move(void)> callback)
{
  (void)callback;
}
