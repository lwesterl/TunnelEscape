/**
  *   @file LevelItem.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for LevelItem
  */

#include "../include/LevelItem.hpp"

// static conversion, left coordinate to center
float LevelItem::convertLeftXCenter(AssetManager::ImageAssets imageAsset, float x) {
  return x + static_cast<float> (AssetManager::getPixmap(imageAsset)->width()/2);
}

// static conversion, upper coordinate to center
float LevelItem::convertUpperYCenter(AssetManager::ImageAssets imageAsset, float y) {
  return y + static_cast<float> (AssetManager::getPixmap(imageAsset)->height()/2);
}

// static conversion, center x to left
float LevelItem::convertCenterXLeft(AssetManager::ImageAssets imageAsset, float x) {
  return x - static_cast<float> (AssetManager::getPixmap(imageAsset)->width()/2);
}

// static conversion, center y to upper edge
float LevelItem::convertCenterYUpper(AssetManager::ImageAssets imageAsset, float y) {
  return y - static_cast<float> (AssetManager::getPixmap(imageAsset)->height()/2);
}

// Consructor
LevelItem::LevelItem(AssetManager::ImageAssets imageAsset, float x, float y):
QGraphicsPixmapItem(*AssetManager::getPixmap(imageAsset)),
imageAsset(imageAsset)
{
  setPosition(x, y);
}

// Get item width
int LevelItem::getWidth() const {
  return pixmap().width();
}

// Get item height
int LevelItem::getHeight() const {
  return pixmap().height();
}

// Set position, convert coordinates
void LevelItem::setPosition(float x, float y) {
  this->x = x - static_cast<float>(getWidth()/2);
  this->y = y - static_cast<float>(getHeight()/2);
  setPos(this->x, this->y);
}

// Check if point is inside LevelItem
bool LevelItem::isInside(float x, float y) {
  if ( (x > this->x) && (x < this->x + getWidth()) ) {
    if ( (y > this->y) && (y < this->y + getHeight()) ) return true;
  }
  return false;
}

// Print implementation
std::ostream& operator<<(std::ostream &os, LevelItem &levelItem) {
  os << AssetManager::getImageAssetStr(levelItem.imageAsset) << "," << levelItem.x
     << "," << levelItem.y << "," << levelItem.getWidth() << "," << levelItem.getHeight() << std::endl;
  return os;
}
