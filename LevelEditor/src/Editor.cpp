/**
  *   @file Editor.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for Editor class
  */

#include "../include/Editor.hpp"

// Init image asset for LevelItem creation
AssetManager::ImageAssets Editor::LevelItemImageAsset = AssetManager::ImageAssets::BlackGround; // this just happens to be the first value
EditorMode Editor::CurrentEditorMode = EditorMode::InsertMode; // change this to PreviewMode

// Consructor
Editor::Editor(QObject *parent): QGraphicsScene(parent) {
  setSceneRect(0, 0, Editor::ScreenWidth, Editor::ScreenHeight);
}

// Deconstructor
Editor::~Editor() {
  ClearLevelItems();
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

// Mouse release event implementation, protected
void Editor::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  //qDebug() << mouseEvent->pos();
}

// Add LevelItem
void Editor::addLevelItem(AssetManager::ImageAssets imageAsset, float x, float y) {
  LevelItem *levelItem = new LevelItem(imageAsset, x, y);
  addItem(levelItem);
  levelItems.push_front(levelItem); // this way newer objects get removed first
}

// Try to remove LevelItems
void Editor::removeLevelItem(float x, float y) {
  for (auto it = levelItems.begin(); it != levelItems.end(); it++) {
    if ((*it)->isInside(x, y)) {
      // remove item
      removeItem(*it);
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
  if (currentItem) {
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
      ClearLevelItems();

      std::string line;
      while (getline(level, line)) {
        std::istringstream lineStream(line);
        float x, y;
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
            }
            i++;
            content.clear();
          } catch (std::invalid_argument &e) {
            qDebug() << "File loading failed: " << e.what();
            // clear whole level
            ClearLevelItems();
            return false;
          }
        }
        if (i == 5) {
          // line read ok, create new LevelItem
          AssetManager::ImageAssets asset = AssetManager::getStrImageAsset(imageAssetName);
          float x_center = LevelItem::convertLeftXCenter(asset, x);
          float y_center = LevelItem::convertUpperYCenter(asset, y);
          addLevelItem(asset, x_center, y_center);
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

// Clear all LevelItems, private method
void Editor::ClearLevelItems() {
  for (auto it = levelItems.begin(); it != levelItems.end(); it++) {
    removeItem(*it); // remove from scene
    delete *it;
  }
  levelItems.clear();
}
