#ifndef	POINT_H
# define POINT_H

# include <array>

# include "Radar.hpp"
# include "PlayerInfo.hpp"

class Point
{
public:
  enum Direction
    {
      LEFT,
      TOPLEFT,
      TOP,
      TOPRIGHT,
      RIGHT,
      BOTTOMRIGHT,
      BOTTOM,
      BOTTOMLEFT
    };

  Point(void);
  virtual ~Point(void) = default;
  Point(const Point& other) = delete;
  Point		&operator=(const Point& other) = delete;

  void			take(PlayerColor player);
  void			free(void);

  PlayerColor		isTaken(void) const;
  Radar			&direction(Direction dir);
  const Radar		&cdirection(Direction dir) const;

  /*
  ** calling this function with any direction returns
  ** an unsigned int containing a length worth
  ** direction.length + oppositeDirection.length
  ** (if same color as Point) + 1
  */
  unsigned		axis(Direction dir) const;
  static Direction	oppositeDirection(Direction dir);

private:
  PlayerColor		_center;
  std::array<Radar, 8>	_directions;
};

#endif /* POINT_H */
