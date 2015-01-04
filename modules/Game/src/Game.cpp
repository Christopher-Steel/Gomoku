#include <functional>


#include "Game.hpp"
#include "Human.hpp"
#include "GameAction.h"

Game::Game(void)
  //_printer(_goban),
{

}

PlayerColor	Game::run()
{
  GameAction gameAction;
  if (!gameAction.initialize(sf::Vector2u(1280, 1080), "Gomoku")) {
    return PlayerColor::BLACK;
  }

  gameAction.run();
  // std::function<APlayer *(PlayerColor)>	playerFactory[] =
  //   {
  //     [](PlayerColor c){ return new Human(c); },
  //     [](PlayerColor c){ return new Human(c); } // replace with AI
  //   };
  // APlayer::Move	move;
  // APlayer	*currentPlayer = nullptr;

  // _black.reset(playerFactory[static_cast<unsigned>(black) - 1](PlayerColor::BLACK));
  // _white.reset(playerFactory[static_cast<unsigned>(white) - 1](PlayerColor::WHITE));

  // _printer.print();
  // currentPlayer = _black.get();
  // while (not _goban.isGameOver()) {
  //   move = currentPlayer->getMove();
  //   if (not _goban.setStone(currentPlayer->getColor(), move.x, move.y)) {
  //     _printer.printIllegalMove();
  //     continue;
  //   }
  //   _printer.print();
  //   currentPlayer = (currentPlayer == _black.get() ? _white.get() : _black.get());
  // }
  // _printer.printVictory(_goban.isGameOver());
  return PlayerColor::BLACK;
}
