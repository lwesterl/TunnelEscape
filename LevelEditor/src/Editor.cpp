/**
  *   @file Editor.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for Editor class
  */

#include "../include/Editor.hpp"

// Init image asset for LevelItem creation
AssetManager::ImageAssets Editor::LevelItemImageAsset = AssetManager::ImageAssets::BlackGround; // this just happens to be the first value
EditorMode Editor::CurrentEditorMode = EditorMode::PreviewMode;
bool Editor::ConnectToPreviousItemsX = false;
bool Editor::ConnectToPreviousItemsY = false;

// Consructor
Editor::Editor(QObject *parent): QGraphicsScene(parent) {
  setSceneRect(0, 0, Editor::ScreenWidth, Editor::ScreenHeight);
}

// Deconstructor
Editor::~Editor() {
  clearLevelItems();
}

// Mouse move event implementation, protected
void Editor::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  float x = mouseEvent->scenePos().x();
  float y = mouseEvent->scenePos().y();
  switch (Editor::CurrentEditorMode) {
    case EditorMode::InsertMode:
      MoveCurrentLevelItem(x, y);
      break;
    case EditorMode::RemoveMode:
      break;
    case EditorMode::PreviewMode:
      break;
  }
}

// Mouse press event implementation, protected
void Editor::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  float x = mouseEvent->scenePos().x();
  float y = mouseEvent->scenePos().y();
  if (mouseEvent->button() == Qt::RightButton) {
    ToggleLevelItemMode(x, y);
  } else {
    switch (Editor::CurrentEditorMode) {
      case EditorMode::InsertMode:
        InsertLevelItem(x, y);
        break;
      case EditorMode::RemoveMode:
        removeLevelItem(x, y);
        break;
      case EditorMode::PreviewMode:
        break;
    }
  }
}

// Add LevelItem
void Editor::addLevelItem(AssetManager::ImageAssets imageAsset, float x, float y, bool imageObject) {
  const int original_x = x;
  if (Editor::ConnectToPreviousItemsX) {
    float x_adjusted = ConnectLevelItemX(x, y, AssetManager::getPixmap(imageAsset)->width());
    if (x_adjusted) x = x_adjusted;
  }
  if (Editor::ConnectToPreviousItemsY) {
    float y_adjusted = ConnectLevelItemY(original_x, y, AssetManager::getPixmap(imageAsset)->height());
    if (y_adjusted) y = y_adjusted;
  }
  LevelItem *levelItem = new LevelItem(imageAsset, x, y, imageObject);
  addItem(levelItem);
  levelItems.push_front(levelItem); // this way newer objects get removed first
  // note: rectMap uses edge coordinates
  rectMap.populateCells( std::pair<int,int> (static_cast<int>(levelItem->getX()), static_cast<int>(levelItem->getY())),
  std::pair<int,int> (static_cast<int>(levelItem->getX() + levelItem->getWidth()), static_cast<int>(levelItem->getY() + levelItem->getHeight())) );
}

// Try to remove LevelItems
void Editor::removeLevelItem(float x, float y) {
  for (auto it = levelItems.begin(); it != levelItems.end(); it++) {
    if ((*it)->isInside(x, y)) {
      // remove item
      removeItem(*it);
      // note: rectMap uses edge coordinates
      rectMap.depopulateCells( std::pair<int,int> (static_cast<int>((*it)->getX()), static_cast<int>((*it)->getY())),
      std::pair<int,int> (static_cast<int>((*it)->getX() + (*it)->getWidth()), static_cast<int>((*it)->getY() + (*it)->getHeight())) );
      delete *it;
      it = levelItems.erase(it);
      return;
    }
  }
}

// Remove current LevelItem
void Editor::removeCurrentLevelItem() {
  if (currentItem) {
    removeItem(currentItem);
    delete currentItem;
    currentItem = nullptr;
  }
}

// Move current LevelItem, protected
void Editor::MoveCurrentLevelItem(float x, float y) {
  const int original_x = x;
  if (currentItem) {
    if (Editor::ConnectToPreviousItemsX) {
      float x_adjusted = ConnectLevelItemX(x, y, currentItem->getWidth());
      if (x_adjusted) x = x_adjusted;
    }
    if (Editor::ConnectToPreviousItemsY) {
      float y_adjusted = ConnectLevelItemY(original_x, y, currentItem->getHeight());
      if (y_adjusted) y = y_adjusted;
    }
    currentItem->setPosition(x, y);
  }
}

// Insert a LevelItem, procted
void Editor::InsertLevelItem(float x, float y) {
  if (currentItem) {
    // remove currentItem and create whole new item to levelItems, this is just easier this way
    removeCurrentLevelItem();
    addLevelItem(Editor::LevelItemImageAsset, x, y);
  } else {
    // create new currentItem and add it to scene
    currentItem = new LevelItem(Editor::LevelItemImageAsset, x, y);
    addItem(currentItem);
  }
}

// Save level to file
bool Editor::saveLevel(const QString &filename) {
  if (ValidateLevelName(filename)) {
    std::ofstream level(filename.toStdString(), std::ios::out | std::ios::trunc);
    if (level.is_open()) {
      // write all LevelItems to the level
      for (LevelItem* levelItem : levelItems) {
        level << *levelItem;
      }
      level.close();
      return true;
    }
  }
  return false;
}

// Load level
bool Editor::loadLevel(const QString &filename) {
  if (ValidateLevelName(filename)) {
    // remove old LevelItems
    std::ifstream level(filename.toStdString(), std::ifstream::in);
    if (level.is_open()) {
      // clear all old LevelItems
      clearLevelItems();

      std::string line;
      while (getline(level, line)) {
        std::istringstream lineStream(line);
        float x, y;
        bool imageObject = false;
        std::string imageAssetName;
        int i = 0;
        std::string content;
        while (getline(lineStream, content, ',')) {
          try {
            switch(i) {
              case 0:
                imageAssetName = content;
                break;
              case 1:
                x = std::stof(content);
                break;
              case 2:
                y = std::stof(content);
                break;
              case 3:
                break; // width currently not used
              case 4:
                break; // height currently not used
              case 5:
                if(content == "ImageObject") imageObject = true;
                break;
            }
            i++;
            content.clear();
          } catch (std::invalid_argument &e) {
            qDebug() << "File loading failed: " << e.what();
            // clear whole level
            clearLevelItems();
            return false;
          }
        }
        if (i == 6) {
          // line read ok, create new LevelItem
          AssetManager::ImageAssets asset = AssetManager::getStrImageAsset(imageAssetName);
          float x_center = LevelItem::convertLeftXCenter(asset, x);
          float y_center = LevelItem::convertUpperYCenter(asset, y);
          addLevelItem(asset, x_center, y_center, imageObject);
        }
      }
    }
    level.close();
    return true;
  }
  return false;
}

// Validate level name, private method
bool Editor::ValidateLevelName(const QString& levelName) const {
  QString regExpr = LevelNameExtension;
  regExpr = regExpr + "$";
  return levelName.contains(QRegularExpression(regExpr));
}

// Clear all LevelItems
void Editor::clearLevelItems() {
  for (auto it = levelItems.begin(); it != levelItems.end(); it++) {
    removeItem(*it); // remove from scene
    delete *it;
  }
  levelItems.clear();
  rectMap.clear();
}

// Connect LevelItem to another one in x dimension, private method
float Editor::ConnectLevelItemX(float x, float y, float width) {
  float x_adjusted = 0.f;
  if (rectMap.isPopulated(static_cast<int>(x), static_cast<int>(y))) {
    int new_x = rectMap.getClosestFreeX(static_cast<int>(x), static_cast<int>(y));
    if (new_x > 0) {
      if (new_x < static_cast<int>(x)) x_adjusted = static_cast<float>(new_x) - 0.5f * width;
      else x_adjusted = static_cast<float>(new_x) + 0.5f * width;
    }
  }
  return x_adjusted;
}

// Connect LevelItem to another one in y dimension, private method
float Editor::ConnectLevelItemY(float x, float y, float height) {
  float y_adjusted = 0.f;
  if (rectMap.isPopulated(static_cast<int>(x), static_cast<int>(y))) {
    int new_y = rectMap.getClosestFreeY(static_cast<int>(x), static_cast<int>(y));
    if (new_y > 0) {
      if (new_y < static_cast<int>(y)) y_adjusted = static_cast<float>(new_y) - 0.5f * height;
      else y_adjusted = static_cast<float>(new_y) + 0.5 * height;
    }
  }
  return y_adjusted;
}

// Toggle LevelItem mode, private method
void Editor::ToggleLevelItemMode(float x, float y) {
  // first find out if there is a object the position
  if (rectMap.isPopulated(static_cast<int>(x), static_cast<int>(y))) {
    // toggle the first object at the position
    for (auto& item : levelItems) {
      if (item->isInside(x, y)) {
        item->toggleMode();
        return;
      }
    }
  }
}
