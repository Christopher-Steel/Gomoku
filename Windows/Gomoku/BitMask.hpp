#ifndef	BITMASK_H
# define BITMASK_H

class BitMask
{
public:

  BitMask(short mask = 0);
  virtual ~BitMask(void) = default;
  BitMask(const BitMask& other) = default;
  BitMask&	operator=(const BitMask& other) = default;

  bool		has(const BitMask& mask) const;
  BitMask&	add(const BitMask& mask);
  BitMask&	rm(const BitMask& mask);

private:

  short		_mask;
};

#endif /* BITMASK_H */
