#pragma once

# include <memory>

# include "Goban.hpp"
# include "GobanPrinter.hpp"
# include "APlayer.hpp"
# include "SFML/Graphics.hpp"

class ModuleGame
{
public:
  ModuleGame(void);
  virtual ~ModuleGame(void) = default;
  ModuleGame(const ModuleGame& other) = delete;
  ModuleGame&	operator=(const ModuleGame& other) = delete;

  PlayerColor	run(unsigned int x, unsigned int y, bool player);
  void      	initPlayer(PlayerType black, PlayerType white);
  unsigned int	*getIndex();

private:
  Goban								_goban;
  GobanPrinter							_printer;
  std::unique_ptr<APlayer>	_black;
  std::unique_ptr<APlayer>	_white;
};
