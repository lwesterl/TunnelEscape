/**
  *   @file Rect.cpp
  *   @author Lauri Westerholm
  *   @brief Contains Rect source code
  */

#include "Rect.hpp"

namespace pe {

  // Empty constructor
  template<typename T>
  Rect<T>::Rect(): width(static_cast<T>(0)), height(static_cast<T>(0)) {}

  // Constructor
  template<typename T>
  Rect<T>::Rect(Vector2<T> upper_left, T width, T height):
  pos(upper_left), width(width), height(height) {}

  // Copy constructor
  template<typename T>
  Rect<T>::Rect(const Rect<T>& rect):
  pos(rect.pos), width(rect.width), height(rect.height) {}

  // Assignment operator
  template<typename T>
  Rect<T>& Rect<T>::operator=(const Rect<T>& rect) {
    pos = rect.pos;
    width = rect.width;
    height = rect.height;
    return *this;
  }

  // Set position
  template<typename T>
  void Rect<T>::setPosition(Vector2<T> position) {
    pos = position;
  }

  // Get position
  template<typename T>
  Vector2<T> Rect<T>::getPosition() const {
    return pos;
  }

  // Set width
  template<typename T>
  void Rect<T>::setWidth(T width) {
    this->width = width;
  }

  // Get width
  template<typename T>
  T Rect<T>::getWidth() const {
    return width;
  }

  // Set height
  template<typename T>
  void Rect<T>::setHeight(T height) {
    this->height = height;
  }

  // Get height
  template<typename T>
  T Rect<T>::getHeight() const {
    return height;
  }

  // Set size
  template<typename T>
  void Rect<T>::setSize(const Vector2<T> size) {
    width = size.x;
    height = size.y;
  }

  // Get size Vector2
  template<typename T>
  Vector2<T> Rect<T>::getSize() const {
    return Vector2<T>(width, height);
  }

  // Check if contains point
  template<typename T>
  bool Rect<T>::contains(T x, T y) const {
    return ((x >= pos.x) && (x <= pos.x + width) && (y >= pos.y) && (y <= pos.y + height));
  }

  // Another form for contains
  template<typename T>
  bool Rect<T>::contains(const Vector2<T>& point) const {
    return ((point.x >= pos.x) && (point.x <= pos.x + width) && (point.y >= pos.y) && (point.y <= pos.y + height));
  }

  //  Instantiate needed templates
  template class Rect<int>;
  template class Rect<float>;
  template class Rect<unsigned>;
  template class Rect<double>;


} // end of namespace pe
