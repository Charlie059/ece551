#include "point.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>

Point::Point() : x(0), y(0) {
}

void Point::move(double dx, double dy) {
  this->x += dx;
  this->y += dy;
}

double Point::distanceFrom(const Point & p) {
  double ans = std::sqrt(

      std::pow((p.x - this->x), 2) + std::pow((p.y - this->y), 2));
  return ans;
}
