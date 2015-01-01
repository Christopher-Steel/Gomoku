#include <functional>


#include "ModuleGame.hpp"
#include "Human.hpp"

#include <iostream>

ModuleGame::ModuleGame(void) :
  _printer(_goban),
  _black(nullptr),
  _white(nullptr)
{
}

void      ModuleGame::initPlayer(PlayerType black, PlayerType white) {
  std::function<APlayer *(PlayerColor)> playerFactory[] =
    {
      [](PlayerColor c){ return new Human(c); },
      [](PlayerColor c){ return new Human(c); } // replace with AI
    };

  _black.reset(playerFactory[static_cast<unsigned>(black) - 1](PlayerColor::BLACK));
  _white.reset(playerFactory[static_cast<unsigned>(white) - 1](PlayerColor::WHITE));
}

PlayerColor	ModuleGame::run(unsigned int x, unsigned int y, bool player)
{
  APlayer *currentPlayer = nullptr;
  if (player == false) {
    //std::cout << "black" << std::endl;
    currentPlayer = _black.get();
  }
  else {
    //std::cout << "white" << std::endl;
    currentPlayer = _white.get();
  }
  if (not _goban.isGameOver()) {
    if (not _goban.setStone(currentPlayer->getColor(), x, y)) {
       _printer.printIllegalMove();
      return PlayerColor::ERROR;
    }
    currentPlayer = (currentPlayer == _black.get() ? _white.get() : _black.get());
  }
  else
    return (PlayerColor::END);
  return _goban.isGameOver();
}
