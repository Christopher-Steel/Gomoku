#ifndef	GAME_H
# define GAME_H

# include <memory>

# include "Goban.hpp"
# include "GobanPrinter.hpp"
# include "APlayer.hpp"
# include "SFML/Graphics.hpp"

class Game
{
public:
  Game(void);
  virtual ~Game(void) = default;
  Game(const Game& other) = delete;
  Game&	operator=(const Game& other) = delete;

  PlayerColor	run(unsigned int x, unsigned int y, bool player);
  void      	initPlayer(PlayerType black, PlayerType white);

private:
  Goban								_goban;
  GobanPrinter							_printer;
  std::unique_ptr<APlayer>	_black;
  std::unique_ptr<APlayer>	_white;


};

#endif /* GAME_H */
