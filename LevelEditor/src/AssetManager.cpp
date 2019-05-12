/**
  *   @file AssetManager.cpp
  *   @author Lauri Westerholm
  *   @brief Contains implementations relating to namespace AssetManager
  */

#include "../include/AssetManager.hpp"

namespace AssetManager {

  std::map<const ImageAssets, const std::string> imagePaths =
  {
    { ImageAssets::BlackGround, "img/BlackGround.png" },
    { ImageAssets::DarkBrownGround, "img/DarkBrownGround.png" },
    { ImageAssets::DarkBrownGroundMarks, "img/DarkBrownGroundMarks.png" },
    { ImageAssets::DeepSky, "img/DeepSky.png" },
    { ImageAssets::Flames, "img/Flames.png" },
    { ImageAssets::GrassMarks, "img/GrassMarks.png" },
    { ImageAssets::Grass, "img/Grass.png" },
    { ImageAssets::GroundGrass, "img/GroundGrass.png" },
    { ImageAssets::LightSky, "img/LightSky.png" },
    { ImageAssets::Player, "img/Player.png" },
    { ImageAssets::End, "img/End.png" }
  };

  std::map<const std::string, const ImageAssets> strToImageAssets =
  {
    { "BlackGround", ImageAssets::BlackGround },
    { "DarkBrownGround", ImageAssets::DarkBrownGround },
    { "DarkBrownGroundMarks", ImageAssets::DarkBrownGroundMarks },
    { "DeepSky", ImageAssets::DeepSky },
    { "Flames", ImageAssets::Flames },
    { "GrassMarks", ImageAssets::GrassMarks },
    { "Grass", ImageAssets::Grass },
    { "GroundGrass", ImageAssets::GroundGrass },
    { "LightSky", ImageAssets::LightSky },
    { "Player", ImageAssets::Player },
    { "End", ImageAssets::End }
  };

  const std::string getImagePath(const ImageAssets imageAsset) { return imagePaths[imageAsset]; }

  ImageAssets getStrImageAsset(const std::string &asset) {
    try {
      return strToImageAssets.at(asset);
    } catch (std::out_of_range &e) {
      qDebug() << e.what();
      return ImageAssets::BlackGround;
    }
  }

  const QPixmap* getPixmap(const ImageAssets imageAsset) { return pixmaps[imageAsset]; }

  // return substring (same as enum value in str format) of path strings
  const std::string getImageAssetStr(const ImageAssets imageAsset) {
    const std::string str = imagePaths[imageAsset];
    // all these paths start with img/ and end with .png
    return str.substr(4, str.size() - 8);
  }

  // Create QPixmaps
  std::map<ImageAssets, QPixmap*> pixmaps;
  void INIT() {
    for (int i = static_cast<int> (ImageAssets::BlackGround); i <= static_cast<int> (ImageAssets::End); i++) {
      pixmaps.emplace(static_cast<ImageAssets>(i), new QPixmap(QString::fromStdString(getImagePath(static_cast<ImageAssets>(i)))));
    }
  }

  // Delete QPixmaps
  void DELETE() {
    for (auto it = pixmaps.begin(); it != pixmaps.end(); it++) {
      delete it->second;
    }
    pixmaps.clear();
  }

} // end of namespace AssetManager
