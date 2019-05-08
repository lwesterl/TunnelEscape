/**
  *   @file AssetManager.hpp
  *   @author Lauri Westerholm
  *   @brief Contains AssetManager namespace
  */

#pragma once
#include <QPixmap>
#include <QString>

#include <string>
#include <map>

/**
  *   @namespace AssetManager
  *   @brief Used for asset relating data structures and functions
  */
namespace AssetManager {

  /**
    *   @enum ImageAssets
    *   @brief Defines constants for all image assets
    */
  enum class ImageAssets:int {
    BlackGround,
    DarkBrownGround,
    DarkBrownGroundMarks,
    DeepSky,
    Flames,
    GrassMarks,
    Grass,
    GroundGrass,
    LightSky
  };

  extern std::map<ImageAssets, const std::string> imagePaths; /**< stores paths of the images */
  extern std::map<ImageAssets, QPixmap*> pixmaps; /**< stores QPixmaps of the images */

  /**
    *   @brief Call this before using getPixmap, allocates QPixmaps
    *   @remark This should be called from the main when program starts
    */
  void INIT();

  /**
    *   @brief Call this when program finishes to deallocate memory used for pixmaps
    *   @remark This should be called from the main when program is about to exit
    */
  void DELETE();

  /**
    *   @brief Get image path
    *   @param imageAsset tells which image path should be returned
    *   @return image path
    */
  const std::string getImagePath(ImageAssets imageAsset);

  /**
    *   @brief Get QPixmap item
    *   @param imageAsset tells which QPixmap should be returned
    *   @return pointer to QPixmap
    */
  const QPixmap* getPixmap(ImageAssets imageAsset);

  /**
    *   @brief Get ImageAsset enum value as string
    *   @return string containing only the enum value (no path)
    */
  const std::string getImageAssetStr(ImageAssets imageAsset);

} // end of namespace AssetManager
