/**
  *   @file Shape.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for Shape
  */


#include "Shape.hpp"


  // Empty constructor
  Shape::Shape(): area(0.f) {}

  // Box shape constructor
  Shape::Shape(float width, float height) {
    width = std::abs(width) / 2.f;
    height = std::abs(height) / 2.f;
    frame.push_back( Vector2f(-width, -height) );
    frame.push_back( Vector2f(width, -height) );
    frame.push_back( Vector2f(width, height) );
    frame.push_back( Vector2f(-width, height) );
    frame.push_back( Vector2f(-width, -height) ); // now the box is closed
    // assign min and max vectors
    min = &frame[0];
    max = &frame[2];
    CenterMass();
    FindAxis();
  }

  //  Copy constructor
  Shape::Shape(const Shape& shape) {
    for (Vector2f item : shape.frame) {
      frame.push_back(item);
    }
    FindMinMax();
    CenterMass();
    FindAxis();
  }

  // Assignment overload
  Shape& Shape::operator=(const Shape& shape) {
    frame.clear();
    for (Vector2f item : shape.frame) {
      frame.push_back(item);
    }
    FindMinMax();
    CenterMass();
    FindAxis();
    return *this;
  }

  // Get mass_center
  Vector2f& Shape::getCenter() {
    return mass_center;
  }

  // Get frame
  const std::deque<Vector2f>& Shape::getFrame() const {
    return frame;
  }

  // Get min
  Vector2f Shape::getMin() const {
    Vector2f vect;
    if (min != nullptr) {
      vect = *min;
    }
    return vect;
  }

  // Get max
  Vector2f Shape::getMax() const {
    Vector2f vect;
    if (max != nullptr) {
      vect = *max;
    }
    return vect;
  }

  // Get area
  float Shape::getArea() const {
    return area;
  }

  // Get amount of edges
  int Shape::getEdges() const {
    int edges = frame.size();
    return edges > 0 ? edges -1 : 0;
  }

  // Get axis
  std::vector<Vector2f>& Shape::getAxis() {
    return axis;
  }

  // Get width
  float Shape::getWidth() const {
    if ((max != nullptr) && (min != nullptr)) {
      return max->getX() - min->getX();
    }
    return 0.f;
  }

  // Get height
  float Shape::getHeight() const {
    if ((max != nullptr) && (min != nullptr)) {
      return max->getY() - min->getY();
    }
    return 0.f;
  }

  // Find min and max from frame, private method
  void Shape::FindMinMax() {
    min = nullptr;
    max = nullptr;
    if (frame.size()) {
      min = &frame[0];
      max = &frame[0];

      for (unsigned i = 1; i < frame.size(); i++) {
        if (frame[i] <= *min) min = &frame[i];
        if (frame[i] >= *max) max = &frame[i];
      }
    }
  }

  // Center of polygon mass, private method
  void Shape::CenterMass() {
    float central_x = 0.f;
    float central_y = 0.f;
    float A = 0.f;
    if (frame.size() > 3) {
      float temp = 0;
      unsigned i = 0;
      for (; i < frame.size() - 1; i++) {
        temp = frame[i].getX() * frame[i + 1].getY() - frame[i + 1].getX() * frame[i].getY();
        A += temp;
        central_x += temp * (frame[i].getX() + frame[i + 1].getX());
        central_y += temp * (frame[i].getY() + frame[i + 1].getY());
      }

      A *= 0.5;
      // use area to determine correct center of mass
      if (A) {
        central_x = central_x / (6 * A);
        central_y = central_y / (6 * A);
      }
      else {
        // smt weird happened
        central_x = 0.f;
        central_y = 0.f;
      }

    }
    else if (frame.size() == 3) {
      // line shape
      central_x = (frame[0].getX() + frame[1].getX()) / 2.f;
      central_y = (frame[0].getY() + frame[1].getY()) / 2.f;
    }

    // also update area
    area = A;
    mass_center = Vector2f(central_x, central_y);
  }

  // Calculate axis of the Shape, private method
  void Shape::FindAxis() {
    int len = getEdges();
    axis = std::vector<Vector2f> (len);
    for (int i = 0; i < len; i++) {
      // axis should be perpendicular to edges of the Shape (-y, x) and |axis| = 1, direction doesn't really matter (use abs)
      axis[i] = Vector2f(-std::abs((frame[i + 1].getY() - frame[i].getY())), std::abs(frame[i + 1].getX() - frame[i].getX()));
      axis[i].normalize();
    }
    RemoveDuplicateAxis();
  }

  // Remove duplicate axis, private method
  void Shape::RemoveDuplicateAxis() {
    std::sort(axis.begin(), axis.end(), [] (const Vector2f& vect1, const Vector2f& vect2){
      return vect1 < vect2;
    });
    auto last = std::unique(axis.begin(), axis.end());
    // remove duplicates permanently
    axis.erase(last, axis.end());
  }

