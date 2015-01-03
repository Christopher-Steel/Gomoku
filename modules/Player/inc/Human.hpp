#ifndef	HUMAN_H
# define HUMAN_H

# include "APlayer.hpp"

class Human : public APlayer
{
public:

  Human(PlayerColor color);
  virtual ~Human(void) = default;
  Human(const Human& other) = delete;
  Human&	operator=(const Human& other) = delete;

  Move		getMove(void) const;
};

#endif /* HUMAN_H */
