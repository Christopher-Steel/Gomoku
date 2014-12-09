#include <functional>


#include "Game.hpp"
#include "Human.hpp"

Game::Game(void) :
  _printer(_goban),
  _black(nullptr),
  _white(nullptr)
{
}

void      Game::initPlayer(PlayerType black, PlayerType white) {
  std::function<APlayer *(PlayerColor)> playerFactory[] =
    {
      [](PlayerColor c){ return new Human(c); },
      [](PlayerColor c){ return new Human(c); } // replace with AI
    };

  _black.reset(playerFactory[static_cast<unsigned>(black) - 1](PlayerColor::BLACK));
  _white.reset(playerFactory[static_cast<unsigned>(white) - 1](PlayerColor::WHITE));
}

PlayerColor	Game::run(unsigned int x, unsigned int y, bool player)
{
  //APlayer::Move move;  
  APlayer *currentPlayer = nullptr;
  //_printer.print();
  if (player == false) {
    currentPlayer = _black.get();
  }
  else {
    currentPlayer = _white.get();
  }
  if (not _goban.isGameOver()) {
    if (not _goban.setStone(currentPlayer->getColor(), x, y)) {
      _printer.printIllegalMove();
      // continue;
    }
    //_printer.print();
    //currentPlayer = (currentPlayer == _black.get() ? _white.get() : _black.get());
  }
  else
    _printer.printVictory(_goban.isGameOver());
  return _goban.isGameOver();
}
