#include <functional>


#include "Game.hpp"
#include "Human.hpp"

Game::Game(void) :
  _printer(_goban),
  _black(nullptr),
  _white(nullptr)
{

}

PlayerColor	Game::run(PlayerType black, PlayerType white)
{
  std::function<APlayer *(PlayerColor)>	playerFactory[] =
    {
      [](PlayerColor c){ return new Human(c); },
      [](PlayerColor c){ return new Human(c); } // replace with AI
    };
  APlayer::Move	move;
  APlayer	*currentPlayer = nullptr;

  _black.reset(playerFactory[static_cast<unsigned>(black) - 1](PlayerColor::BLACK));
  _white.reset(playerFactory[static_cast<unsigned>(white) - 1](PlayerColor::WHITE));

  _printer.print();
  currentPlayer = _black.get();
  while (not _goban.isGameOver()) {
    move = currentPlayer->getMove();
    if (not _goban.setStone(currentPlayer->getColor(), move.x, move.y)) {
      _printer.printIllegalMove();
      continue;
    }
    _printer.print();
    //currentPlayer = (currentPlayer == _black.get() ? _white.get() : _black.get());
  }
  _printer.printVictory(_goban.isGameOver());
  return _goban.isGameOver();
}
