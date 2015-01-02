#include "BitMask.hpp"

BitMask::BitMask(short mask) :
  _mask(mask)
{

}

bool		BitMask::has(const BitMask& mask) const
{
  return _mask & mask._mask;
}

BitMask&	BitMask::add(const BitMask& mask)
{
  _mask |= mask._mask;
  return *this;
}

BitMask&	BitMask::rm(const BitMask& mask)
{
  _mask &= ~mask._mask;
  return *this;
}
