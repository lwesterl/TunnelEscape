/**
  *   @file Shape.hpp
  *   @author Lauri Westerholm
  *   @brief Header for Shape
  */


#pragma once

#include "Vector2.hpp"
#include <deque>
#include <vector>
#include <cmath>
#include <algorithm>

  /**
    *   @class Shape
    *   @brief Contains PhysicsObject shape (polygon)
    *   @details Shapes are implemented such a way that they can be reused for multiple
    *   PhysicsObjects (same style PhysicsObjects can share same Shape pointer)
    */
    class Shape
    {
      public:
        /**
          *   @brief Empty constructor
          *   @details Creates an empty shape
          */
        Shape();

        /**
          *   @brief Constructor for box shape
          *   @param width box width
          *   @param height box height
          *   @remark width and height should be > 0 (abs is taken)
          */
        Shape(float width, float height);

        /**
          *   @brief Copy constructor
          *   @param shape Shape to be copied
          */
        Shape(const Shape& shape);

        /**
          *   @brief Assignment overload
          *   @param shape shape to be copied
          *   @return Shape which is identical to shape
          */
        Shape& operator=(const Shape& shape);

        inline Shape* getPointer() { return this; }

        /**
          *   @brief Get the center of mass of Shape
          *   @return reference to mass_center
          */
        Vector2f& getCenter();

        /**
          *   @brief Get the Shape frame
          *   @return frame as constant reference
          */
        const std::deque<Vector2f>& getFrame() const;

        /**
          *   @brief Get min
          *   @return Vector2f matching min
          *   @details Returns an empty pe::Vector2f if min is nullptr
          */
        Vector2f getMin() const;

        /**
          *   @brief Get max
          *   @return Vector2f matching max
          *   @details Returns an empty pe::Vector2f if max is nullptr
          */
        Vector2f getMax() const;

        /**
          *   @brief Get area of the Shape
          *   @return area
          */
        float getArea() const;

        /**
          *   @brief Get how many edges there are in the Shape
          *   @details Should be frame.size() - 1 for all polygon Shapes
          *   @return amount of edges
          *   @remark returns 0 if frame is empty. !!!! This may or may not be same as
          *   axis.size() !!!!
          */
        int getEdges() const;

        /**
          *   @brief Get axis of the Shape
          *   @return axis
          *   @details These axis are used by CollisionDetection. They are precomputed
          *   after Shape is created to save compute time in CollisionDetection
          */
        std::vector<Vector2f>& getAxis();

        /**
          *   @brief Get Shape width
          *   @return max x coordinate - min x coordinate
          *   @remark returns 0 if min or max nullptr
          */
        float getWidth() const;

        /**
          *   @brief Get Shape height
          *   @return max y coordinate - min y coordinate
          *   @remark returns 0 if min or max nullptr
          */
        float getHeight() const;


      private:

        /**
          *   @brief Search through frame to find min and max Vector2fs
          *   @details Sets pointer to correct frame indexes
          */
        void FindMinMax();

        /**
          *   @brief Calculate polygon center of mass
          *   @details assigns center of mass to mass_center. Uses basic formula which defines
          *   centroid for polygon shapes. Calculates also area of Shape
          */
        void CenterMass();

        /**
          *   @brief Calculate axis of the Shape
          *   @remark This can't be called before frame is fully created and it must be
          *   called from constructor or when frame is changed
          */
        void FindAxis();

        /**
          *   @brief Remove duplicate axis
          *   @details This should be called from FindAxis after all axis have been created
          *   to remove duplicates -> boosts CollisionDetection performance
          */
        void RemoveDuplicateAxis();


        Vector2f mass_center; /**< This should be object mass center point */
        std::deque<Vector2f> frame; /**< Object frame, polygon of connected Vector2f */
        std::vector<Vector2f> axis; /**< Object axes, formet from edges */
        Vector2f* max = nullptr; /**< Should point to the biggest entry in frame */
        Vector2f* min = nullptr; /**< Should point to the smallest entry in frame */
        float area; /**< Area of the Spape */

    };

