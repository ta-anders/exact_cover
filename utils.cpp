#include <iostream>

struct Coords
{
  int x, y;
};

std::ostream& operator<< (std::ostream &out, const Coords &coords)
{
  out << "Coords(x=" << coords.x << ",y=" << coords.y << ")";
  return out;
}

Coords GetCoordsFromPosition(const int position)
{
  const int x = position / 9;
  const int y = position % 9;

  return Coords {x, y};
}
