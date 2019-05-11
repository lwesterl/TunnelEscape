/**
  *   @file RectMap.hpp
  *   @author Lauri Westerholm
  *   @brief Contains RectMap
  */


#pragma once
#include <utility>

#define SCREEN_WIDTH 20000
#define SCREEN_HEIGHT 10000

/**< Macro which makes class non-copyable */
#define NON_COPYABLE(Typename) \
  Typename(const Typename&) = delete; \
  Typename& operator=(const Typename&) = delete

/**
  *   @class RectMap
  *   @brief Contains matrix of the level which tells whether position is already
  *   occupied
  */
class RectMap {
  public:

    /**
      *   @brief Consructor, inits cells
      */
    RectMap();

    /**
      *   @brief Deconstructor
      */
    virtual ~RectMap();

    /**
      *   @brief Populate cells, i.e. add one to the cell value
      *   @param start pair containing indexes for x, y values from which fulfilling is started
      *   @param end pair containing indexes for x, y values where fulfilling is ended
      */
    void populateCells(const std::pair<int, int> &start, const std::pair<int, int> &end);

    /**
      *   @brief Depopulate cells, i.e. add remove one from the cell value, cell population >= 0
      *   @param start pair containing indexes for x, y values from which fulfilling is started
      *   @param end pair containing indexes for x, y values where fulfilling is ended
      */
    void depopulateCells(const std::pair<int, int> &start, const std::pair<int, int> &end);

    /**
      *   @brief Check whether cell is populated or not
      *   @param x position x coordinate
      *   @param y position y coordinate
      *   @return true if populated, otherwise false
      *   @remark This is a fast lookup, can be called often
      */
    bool isPopulated(const int x, const int y) const;

    /**
      *   @brief Get closest x value which is free
      *   @param x position x coordinate
      *   @param y position y coordinate
      *   @details This won't take account object width and doesn't alter y value
      *   @return index of closest free x, on error return -1
      */
    int getClosestFreeX(const int x, const int y) const;

    /**
      *   @brief Get closest y value which is free
      *   @param x position x coordinate
      *   @param y position y coordinate
      *   @details This won't take account object height and doesn't alter x value
      *   @return index of closest free y, on error return -1
      */
    int getClosestFreeY(const int x, const int y) const;

    /**
      *   @brief Clear cells entirely
      */
    void clear();

  private:

    /**
      *   @brief Check position valid
      *   @param x position x coordinate
      *   @param y position y coordinate
      *   @return true if valid, otherwise false
      */
    inline bool CheckPosValid(const int x, const int y) const {
      return (x >= 0) && (x < SCREEN_WIDTH) && (y >= 0) && (y < SCREEN_HEIGHT);
    }

    NON_COPYABLE(RectMap);

    int **cells; /** tells how many object is in the cell */
};
