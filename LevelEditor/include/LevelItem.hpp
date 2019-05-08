/**
  *   @file LevelItem.hpp
  *   @author Lauri Westerholm
  *   @brief Contains LevelItem class
  */

#pragma once
#include "AssetManager.hpp" // Note INIT AssetManager in main.cpp

#include <QGraphicsPixmapItem>
#include <ostream>

/**
  *   @class LevelItem
  *   @brief class which represent one item in LevelEditor, can be drawn
  */
class LevelItem: public QGraphicsPixmapItem {
  public:

    /**
      *   @brief Consructor
      *   @param imageAsset correct image for drawing
      *   @param x position x coordinate, this will convert mouse center coordinate
      *   to item left corner coordinate
      *   @param y position y coordinate, this will convert mouse center coordinate
      *   to item upper corner coordinate
      */
    LevelItem(AssetManager::ImageAssets imageAsset, float x, float y);

    /**
      *   @brief Get item width
      *   @return matching pixmap width
      */
    int getWidth() const;

    /**
      *   @brief Get item height
      *   @return matching pixmap height
      */
    int getHeight() const;

    /**
      *   @brief Set position
      *   @param x center x coordinate, converted to matching left edge coordinate
      *   @param y center y coordinate, converted to matching upper edge coordinate
      */
    void setPosition(float x, float y);

    /**
      *   @brief Get left edge x coordinate
      *   @return x
      */
    inline float getX() { return x; }

    /**
      *   @brief Get upper edge y coordinate
      *   @return y
      */
    inline float getY() { return y; }

    /**
      *   @brief Check whether a point is inside LevelItem or not
      *   @param x mouse center x coordinate
      *   @param y mouse center y coordinate
      *   @return true if point inside LevelItem, otherwise false
      *   @remark Object edges are excluded
      */
    bool isInside(float x, float y);

    /**
      *   @brief Print overload, used to create level file
      *   @return modified handle to the stream which has LevelItem printed out
      *   @details Print format:
          ImageAsset,x,y,width,height
      */

    friend std::ostream& operator<<(std::ostream &os, LevelItem &levelItem);

  private:
    AssetManager::ImageAssets imageAsset;
    float x;
    float y;
};
