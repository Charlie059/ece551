#include "circle.hpp"

#include <cmath>
#include <cstdlib>

Circle::Circle(Point setCenter, const double setRadius) :
    center(setCenter),
    radius(setRadius) {
}

void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double R = this->radius;
  double r = otherCircle.radius;
  double d = std::abs(this->center.distanceFrom(otherCircle.center));
  if (d > (R + r)) {
    return 0;
  }
  if (d <= std::abs(R - r)) {
    if (R > r)
      return M_PI * std::pow(r, 2);
    else
      return M_PI * std::pow(R, 2);
  }

  double RHS_b = (std::pow(d, 2) + std::pow(r, 2) - std::pow(R, 2)) / (2 * d * r);
  double LHS_b = (std::pow(d, 2) - std::pow(r, 2) + std::pow(R, 2)) / (2 * d * R);
  double s0 = d + r - R;
  double s1 = d - r + R;
  double s2 = -d + r + R;
  double s3 = d + r + R;
  double sth = std::pow(s0 * s1 * s2 * s3, 0.5);
  double ans = std::pow(r, 2) * std::acos(RHS_b) + std::pow(R, 2) * std::acos(LHS_b) -
               (1.0 / 2.0) * sth;
  return ans;
}
