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
  for (auto it = levelItems.begin(); it != levelItems.end(); it++) {
    removeItem(*it); // remove from scene
    delete *it;
  }
  levelItems.clear();
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
void Editor::addLevelItem(float x, float y) {
  LevelItem *levelItem = new LevelItem(Editor::LevelItemImageAsset, x, y);
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
    addLevelItem(x, y);
  } else {
    // create new currentItem and add it to scene
    currentItem = new LevelItem(Editor::LevelItemImageAsset, x, y);
    addItem(currentItem);
  }
}
