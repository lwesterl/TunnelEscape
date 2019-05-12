/**
  *   @file AssetManager.hpp
  *   @author Lauri Westerholm
  *   @brief Contains AssetManager namespace
  */

#pragma once
#include <QPixmap>
#include <QString>
#include <QDebug>

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
    *   @remark TO ADD IMAGES, ADD IMAGE TYPE NAME TO THIS ENUM, ADD IT INTO THE
    *   MAPS AND CHANGE AssetManager.cpp line 62 and EditorWindow.cpp line 56 accordingly
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
    LightSky,
    Player,
    End
  };

  extern std::map<const ImageAssets, const std::string> imagePaths; /**< stores paths of the images */
  extern std::map<const std::string, const ImageAssets> strToImageAssets; /**< maps strings to ImageAssets */
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
  const std::string getImagePath(const ImageAssets imageAsset);

  /**
    *   @brief Get ImageAsset matching string
    *   @return correct ImageAssets value. returns ImageAssets::BlackGround if
    *   string doesn't match to any ImageAssets
    */
  ImageAssets getStrImageAsset(const std::string &asset);

  /**
    *   @brief Get QPixmap item
    *   @param imageAsset tells which QPixmap should be returned
    *   @return pointer to QPixmap
    */
  const QPixmap* getPixmap(const ImageAssets imageAsset);

  /**
    *   @brief Get ImageAsset enum value as string
    *   @return string containing only the enum value (no path)
    */
  const std::string getImageAssetStr(const ImageAssets imageAsset);

} // end of namespace AssetManager
