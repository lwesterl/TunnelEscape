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
      *   @brief Convert left x coordinate to center coordinate
      *   @param imageAsset tells correct pixmap for the conversion
      *   @param x left edge coordinate
      */
    static float convertLeftXCenter(AssetManager::ImageAssets imageAsset, float x);

    /**
      *   @brief Convert upper y coordinate to center coordinate
      *   @param imageAsset tells correct pixmap for the conversion
      *   @param y upper edge coordinate
      */
    static float convertUpperYCenter(AssetManager::ImageAssets imageAsset, float y);

    /**
      *   @brief Convert center x coordinate to left edge coordinate
      *   @param imageAsset tells correct pixmap for the conversion
      *   @param x center x coordinate
      */
    static float convertCenterXLeft(AssetManager::ImageAssets imageAsset, float x);

    /**
      *   @brief Convert center y coordinate to upper edge coordinate
      *   @param imageAsset tells correct pixmap for the conversion
      *   @param y center y coordinate
      */
    static float convertCenterYUpper(AssetManager::ImageAssets imageAsset, float y);


    /**
      *   @brief Consructor
      *   @param imageAsset correct image for drawing
      *   @param x position x coordinate, this will convert mouse center coordinate
      *   to item left corner coordinate
      *   @param y position y coordinate, this will convert mouse center coordinate
      *   to item upper corner coordinate
      *   @param imageObject Whether this is an actual physical object or just an image
      *   if true this is just an image
      */
    LevelItem(AssetManager::ImageAssets imageAsset, float x, float y, bool imageObject = false);

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
      *   @brief Toggle imageObject value
      */
    void toggleMode();

    /**
      *   @brief Print overload, used to create level file
      *   @return modified handle to the stream which has LevelItem printed out
      *   @details Print format:
          ImageAsset,x,y,width,height
      */

    friend std::ostream& operator<<(std::ostream &os, LevelItem &levelItem);

  private:

      static constexpr float ImageOpacity = 0.7f; /**< opacity value for LevelItems for which imageObject is true */

    /**
      *   @brief Set pixmap opacity
      *   @details opacity is set based on imageObject value, true ->
      *   LevelItem half clear
      */
    void SetPixmapOpacity();

    AssetManager::ImageAssets imageAsset;
    float x;
    float y;
    bool imageObject; /**< if true means that this should be only created as image, no physical counterpart */
};
