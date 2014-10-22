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

  _black.reset(playerFactory[static_cast<unsigned>(black) - 1](PlayerColor::BLACK));
  _white.reset(playerFactory[static_cast<unsigned>(white) - 1](PlayerColor::WHITE));

  while (true) {
    move = _black->getMove();
    _goban.setPawn(_black->getColor(), move.x, move.y);
    _printer.print();
    move = _white->getMove();
    _goban.setPawn(_white->getColor(), move.x, move.y);
    _printer.print();
  }
}
