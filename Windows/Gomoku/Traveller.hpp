#ifndef	TRAVELLER_H
# define TRAVELLER_H

# include "Goban.hpp"
# include "Point.hpp"

class Traveller
{
public:
  static unsigned	travel(unsigned index, Point::Direction dir,
			       bool &out_of_bounds, unsigned distance = 1);

private:
  static unsigned	_travelLeft		(unsigned index, bool &out_of_bounds);
  static unsigned	_travelTopLeft		(unsigned index, bool &out_of_bounds);
  static unsigned	_travelTop		(unsigned index, bool &out_of_bounds);
  static unsigned	_travelTopRight		(unsigned index, bool &out_of_bounds);
  static unsigned	_travelRight		(unsigned index, bool &out_of_bounds);
  static unsigned	_travelBottomRight	(unsigned index, bool &out_of_bounds);
  static unsigned	_travelBottom		(unsigned index, bool &out_of_bounds);
  static unsigned	_travelBottomLeft	(unsigned index, bool &out_of_bounds);
};

#endif /* TRAVELLER_H */
