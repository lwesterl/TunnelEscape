/**
  *   @file LevelItem.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for LevelItem
  */

#include "../include/LevelItem.hpp"


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
