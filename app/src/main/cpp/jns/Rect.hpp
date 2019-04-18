/**
  *   @file Rect.hpp
  *   @author Lauri Westerholm
  *   @brief Header for templated Rect class
  */

#pragma once

#include "Vector2.hpp"
#include <ostream>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  /**
    *   @class Rect
    *   @brief Template class for rectangles
    */
  template<typename T>
  class Rect
  {
    public:
      /**
        *   @brief Empty constructor
        */
      Rect();

      /**
        *   @brief Construct spesific rect
        *   @param upper_left upper_left corner coordinate
        *   @param width Rect width
        *   @param height Rect height
        */
      Rect(Vector2<T> upper_left, T width, T height);

      /**
        *   @brief Copy constructor
        *   @param rect Rect to be copied
        */
      Rect(const Rect<T>& rect);

      /**
        *   @brief Assignment operator overload
        *   @param rect Rect which is copied
        *   @return updated Rect refence
        */
      Rect<T>& operator=(const Rect<T>& rect);

      /**
        *   @brief Set position for Rect
        *   @param position Rect pos
        */
      void setPosition(Vector2<T> position);

      /**
        *   @brief Get Rect position
        *   @return pos Vector2
        */
      Vector2<T> getPosition() const;

      /**
        *   @brief Set Rect width
        *   @param width new Rect width
        */
      void setWidth(T width);

      /**
        *   @brief Get width
        *   @return width
        */
      T getWidth() const;

      /**
        *   @brief Set height
        *   @param height new Rect height
        */
      void setHeight(T height);

      /**
        *   @brief Get height
        *   @return height
        */
      T getHeight() const;

      /**
        *   @brief Set size as Vector2
        *   @param size new size
        */
      void setSize(const Vector2<T>size);

      /**
        *   @brief Get size as Vector2
        *   @return Rect size
        */
      Vector2<T> getSize() const;

      /**
        *   @brief Check if Rect contains a point
        *   @param x x coordinate
        *   @param y y coordinate
        *   @return true if Rect contains the point, otherwise false
        *   @remark Inclusive for Rect frame
        */
      bool contains(T x, T y) const;

      /**
        *   @brief Check if Rect contains a point
        *   @param point the point of interest as Vector2
        *   @return true if Rect contains the point, otherwise false
        *   @remark Inclusive for Rect frame
        */
      bool contains(const Vector2<T>& point) const;

      /**
        *   @brief operator<< overload
        *   @param os output stream
        *   @param rect Rect to be printed out
        *   @return updated ostream
        */
      friend std::ostream& operator<<(std::ostream& os, const Rect<T>& rect) {
        os << "Rect upper left corner: " << rect.pos << "width: " << rect.width << ", height: " << rect.height << std::endl;
        return os;
      }

      /**
        *   @brief Equality operator
        *   @param rect1 1st Rect to be compared
        *   @param rect2 2nd Rect to be compared
        *   @return true if Rects identical, otherwise false
        */
      friend bool operator==(const Rect<T>& rect1, const Rect<T>& rect2) {
        return ((rect1.pos == rect2.pos) && (rect1.width == rect2.width) && (rect1.height == rect2.height));
      }

      /**
        *   @brief Smaller than operator
        *   @param rect1 1st Rect to be compared
        *   @param rect2 2nd Rect to be compared
        *   @return pos based comparison result @see Vector2::operator<
        */
      friend bool operator<(const Rect<T>& rect1, const Rect<T>& rect2) {
        return rect1.pos < rect2.pos;
      }

      /**
        *   @brief Greater than operator
        *   @param rect1 1st Rect to be compared
        *   @param rect2 2nd Rect to be compared
        *   @return pos based comparison result @see Vector2::operator>
        */
      friend bool operator>(const Rect<T>& rect1, const Rect<T>& rect2) {
        return rect1.pos > rect2.pos;
      }


    private:
      Vector2<T> pos; /**< upper_left corner of the Rect */
      T width;
      T height;
  };

  // shorter keywords
  typedef Rect<float> Rectf; /**< typedef for float Rect */
  typedef Rect<int> Recti; /**< typedef for int Rect */
  typedef Rect<unsigned> Rectu; /**< typedef for unsigned Rect */
  typedef Rect<double> Rectd; /**< typedef for double Rect */

} // end of namespace pe
