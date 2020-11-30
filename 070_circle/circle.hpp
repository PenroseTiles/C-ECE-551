#include "point.hpp"

class Circle {
 private:
  Point centre;
  const double radius;

 public:
  Circle(Point p, double r) : centre(p), radius(r) {}
  void move(double dx, double dy);
  double getSectorArea(double y) const;
  double getTriangleArea(double y) const;
  double getSegmentArea(double y) const;
  double intersectionArea(const Circle & otherCircle);
};
