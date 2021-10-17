#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point, const double);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
