/**
  *   @file Vector2.hpp
  *   @author Lauri Westerholm
  *   @brief Vector2 Header
  *   @details Contains class for representing 2D-vectors
  */

#pragma once

#include <ostream>
#include <cmath>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  template<typename T> class Rect; /**< Forward declaration of Rect template class */

  /**
    *   @class Vector2
    *   @brief Template class for 2D-vectors
    */

  template <typename T>
  class Vector2
  {
    public:
      /**
        *   @brief Standard constructor
        *   @param x x coordinate
        *   @param y y coordinate
        */
      Vector2(T x, T y);

      /**
        *   @brief Empty constructor
        *   @remark sets x and y to 0
        */
      Vector2();

      /**
        *   @brief Copy constructor
        *   @param vector2 Vector2 instance to be copied
        */
      Vector2(const Vector2<T>& vector2);

      /**
        *   @brief Cast to another Vector2 type
        *   @return Vector2 of the casted type
        */
      template<typename N>
      operator Vector2<N>() {
        return Vector2<N>(static_cast<N>(x), static_cast<N>(y));
      }

      /**
        *   @brief Get x value
        *   @return x
        */
      T getX() const;

      /**
        *   @brief Get y value
        *   @return y
        */
      T getY() const;

      /**
        *   @brief Update x and y values
        *   @param x new x value
        *   @param y new y value
        */
      void update(T x, T y);

      /**
        *   @brief Normalize Vector2
        *   @details Divides Vector2 by its norm
        */
      void normalize();

      /**
        *   @brief Dot product for Vector2
        *   @param vector another Vector2 in relation dot product is calculated
        *   @return dot product of the vectors
        *   @remark dotProduct also available as external function
        */
      float dotProduct(const Vector2<T>& vector) const;

      /**
        *   @brief Rotate Vector2
        *   @param angle Rotation angle in radians
        *   @details This cannot work for integers: only practical for floats and
        *   doubles. unsigned is absolute no no. angle must be in radians and counter-
        *   clockwise
        *   @return updated Vector2
        */
      Vector2<T>& rotate(T angle);

      /**
        *   @brief Get Vector2 angle
        *   @return angle in radians
        *   @remark This is practical for only floats and doubles. Don't use this
        *   for Vector2<unsigned>
        */
      T getAngle() const;

      /**
        *   @brief Get Vector2 length
        *   @return vector component based length (amplitude)
        */
      T getLength() const;

      /**
        *   @brief Assignment operator
        *   @param vector2 Reference instance
        */
      Vector2<T>& operator=(const Vector2<T>& vector2);

      /**
        *   @brief Multiplication by number
        *   @param mult multiplier
        *   @return updated Vector2 refence
        */
      Vector2<T>& operator*=(T mult);

      /**
        *   @brief Addition += -operator overload
        *   @param vector2 Vector2 to be added
        *   @return updated Vector2 reference
        */
      Vector2<T>& operator+=(const Vector2<T>& vector2);

      /**
        *   @brief -= -operator overload
        *   @param vector2 Vector2 to be substracted
        *   @return updated Vector2 reference
        */
      Vector2<T>& operator-=(const Vector2<T>& vector2);

      /**
        *   @brief Equality implementation
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if x and y equal, otherwise false
        */
      friend bool operator==(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x == vect2.x) && (vect1.y == vect2.y) );
      }

      /**
        *   @brief Greater than overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are greater than those of vect2
        */
      friend bool operator>(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x > vect2.x) && (vect1.y > vect2.y) );
      }

      /**
        *   @brief Less than overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are less than those of vect2
        */
      friend bool operator<(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x < vect2.x) && (vect1.y < vect2.y) );
      }

      /**
        *   @brief Greater than or equal to overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are greater or equal than those of vect2
        */
      friend bool operator>=(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x >= vect2.x) && (vect1.y >= vect2.y) );
      }

      /**
        *   @brief Less than or equal to overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are less than or equal to those of vect2
        */
      friend bool operator<=(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x <= vect2.x) && (vect1.y <= vect2.y) );
      }

      /**
        *   @brief multiplication overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return Vector2 which is original vectors multiplied
        */
      friend Vector2<T> operator*(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return Vector2<T>(vect1.x * vect2.x, vect1.y * vect2.y);
      }

      /**
        *   @brief multiplication by multiplier
        *   @param vect to be muliplied
        *   @param multiplier number multiplier
        *   @return new Vector2 which is multiplied
        */
      friend Vector2<T> operator*(const Vector2<T>& vect, T multiplier) {
        return Vector2<T>(vect.x * multiplier, vect.y * multiplier);
      }

      /**
        *   @brief multiplication by multiplier
        *   @param vect to be muliplied
        *   @param multiplier number multiplier
        *   @return new Vector2 which is multiplied
        */
      friend Vector2<T> operator*(T multiplier, const Vector2<T>& vect) {
        return Vector2<T>(vect.x * multiplier, vect.y * multiplier);
      }

      /**
        *   @brief addition overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return Vector2 which is sum of the original vectors
        */
      friend Vector2<T> operator+(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return Vector2<T>(vect1.x + vect2.x, vect1.y + vect2.y);
      }

      /**
        *   @brief substraction overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return Vector2 which is sum of the original vectors
        */
      friend Vector2<T> operator-(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return Vector2<T>(vect1.x - vect2.x, vect1.y - vect2.y);
      }

      /**
        *   @brief <<-operator overload
        *   @param os output ostream
        *   @param vector2 Constant Vector2 instance
        */
      friend std::ostream& operator<<(std::ostream &os, const Vector2<T> &vector2) {
        os << "X: " << vector2.x << ", Y: " << vector2.y << std::endl;
        return os;
      }

      /**
        *   @brief Function implementation for dotproduct
        *   @param vect1 1st Vector2
        *   @param vect2 2nd Vector2
        *   @return dot product of the vectors
        *   @remark dotProduct also available as member method
        */
      friend T dotProduct(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return vect1.x * vect2.x + vect1.y * vect2.y;
      }


    private:
      friend class Rect<T>; /**< Give Rect direct access to x and y */
      T x;
      T y;
  };

  /* shorter keywords */
  typedef Vector2<float> Vector2f; /**< typedef for float Vector2 */
  typedef Vector2<int> Vector2i; /**< typedef for int Vector2 */
  typedef Vector2<double> Vector2d; /**< typedef for double Vector2 */
  typedef Vector2<unsigned> Vector2u; /**< typedef for unsigned Vector2 */

} // end of namespace pe
