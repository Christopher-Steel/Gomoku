#ifndef	HUMAN_H
# define HUMAN_H

# include "APlayer.hpp"

class Human : public APlayer
{
public:

  Human(PlayerColor color);
  virtual ~Human(void) {};
 

  Move		getMove(void) const;
private:
 Human(const Human& other);
  Human&	operator=(const Human& other);
};

#endif /* HUMAN_H */
