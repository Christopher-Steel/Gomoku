#ifndef	RADAR_H
# define RADAR_H

struct Radar
{
  unsigned char color : 2;
  unsigned char open : 1;
  unsigned char length : 5;
};

#endif /* RADAR_H */
