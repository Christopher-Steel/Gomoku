#ifndef	PLAYERINFO_H
# define PLAYERINFO_H

enum PlayerColor
  {
    NONE	= 0x0000,
    WHITE	= 0x0001,
    BLACK	= 0x0002
  };

enum class PlayerType : char
  {
    NONE,
    HUMAN,
    AI
  };

#endif /* PLAYERINFO_H */
