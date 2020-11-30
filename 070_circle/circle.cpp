#include "circle.hpp"
#define PI 3.14159
#include <cmath>

void Circle::move(double dx, double dy) {
  centre.move(dx, dy);
}

double Circle::getSectorArea(double y) const {
  return radius * radius * std::asin(y / radius);
}

double Circle::getTriangleArea(double y) const {
  return y * std::sqrt(radius * radius - y * y);
}

double Circle::getSegmentArea(double y) const {
  return getSectorArea(y) - getTriangleArea(y);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  const double distance = centre.distanceFrom(otherCircle.centre);
  if (distance >= radius + otherCircle.radius) {
    return 0.0;
  }
  if (distance <= std::abs(radius - otherCircle.radius)) {
    return PI * pow(fmin(radius, otherCircle.radius), 2);
  }
  const double a_ = pow(radius, 2);
  const double b_ = pow(otherCircle.radius, 2);
  const double mid_d1 = (a_ - b_ + pow(distance, 2)) / (2 * distance);
  const double mid_d2 = distance - mid_d1;
  const double height = sqrt(pow(radius, 2) - pow(mid_d1, 2));

  const double alpha = std::fmod(std::atan2(height, mid_d1) * 2.0 + 2 * PI, 2 * PI);
  const double beta = std::fmod(std::atan2(height, mid_d2) * 2.0 + 2 * PI, 2 * PI);

  const double area1 = std::pow(radius, 2) / 2.0 * (alpha - std::sin(alpha));
  const double area2 = std::pow(otherCircle.radius, 2) / 2.0 * (beta - std::sin(beta));
  return area1 + area2;
}
