/**
  *   @file Editor.hpp
  *   @author Lauri Westerholm
  *   @brief Contains Editor class
  */

#pragma once
#include "AssetManager.hpp"
#include "LevelItem.hpp"
#include "RectMap.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QRegularExpression>
#include <QDebug>
#include <deque>
#include <fstream>
#include <sstream>
#include <string>

#define LevelNameExtension ".tescape" /**< file extension used */
#define LevelNameExtensionPattern "*.tescape" /**< pattern for level file extension */

/**
  *   @enum EditorMode
  *   @brief Used to detect current editor mode
  */
enum class EditorMode: int {
  PreviewMode = 0, /**< No insertion or removal allowed */
  InsertMode = 1, /**< Possible to insert new LevelItems */
  RemoveMode = 2 /**< Possible to remove existing LevelItems */
};



/**
  *   @class Editor
  *   @brief Handles the level editing
  */

class Editor: public QGraphicsScene {
  Q_OBJECT

  public:
    static const int ScreenWidth = SCREEN_WIDTH; /**< Screen width */
    static const int ScreenHeight = SCREEN_HEIGHT; /**< Screen height */
    static AssetManager::ImageAssets LevelItemImageAsset; /**< image asset used to create LevelItems */
    static EditorMode CurrentEditorMode; /**< This should changed via EditorWindow */
    static bool ConnectToPreviousItemsX; /**< This tells whether new LevelItems should be connected to previous items in x dimension */
    static bool ConnectToPreviousItemsY; /**< This tells whether new LevelItems should be connected to previous items in y dimension */

    /**
      *   @brief Constructor
      *   @param parent paren QObject
      */
    Editor(QObject *parent);

    /**
      *   @brief Deconstructor
      */
    virtual ~Editor();

    /**
      *   @brief Add new LevelItem to the level
      *   @param imageAsset tells which image is used for the LevelItem
      *   @param x mouse center x coordinate
      *   @param y mouse center y coordinate
      */
    void addLevelItem(AssetManager::ImageAssets imageAsset, float x, float y);

    /**
      *   @brief Try to remove LevelItem from the level
      *   @param x mouse center x coordinate
      *   @param y mouse center y coordinate
      *   @remark This is slow, linear time complexity. However, if this becomes sluggish
      *   then the level will most likely also play really sluggishly
      *   @details Tries to remove first a newer object which is pushed to the
      *   front of the container
      */
    void removeLevelItem(float x, float y);

    /**
      *   @brief Remove current LevelItem
      *   @details removes the item from scene and deallocates memory
      */
    void removeCurrentLevelItem();

    /**
      *   @brief Save level to file
      *   @param filename name for the new level
      *   @return true if saving successful, otherwise false
      */
    bool saveLevel(const QString &filename);

    /**
      *   @brief Load level, this will erase old level content
      *   @param filename tries to load this file
      *   @return true if loading successful, otherwise false
      *   @details Expects that the level is comma separated and contains one
      *   LevelItem per line. The format should be same as LevelItem print format
      */
    bool loadLevel(const QString &filename);

    /**
      *   @brief Clear all levelItems
      */
    void clearLevelItems();


  protected:
    /**
      *   @brief Mouse move event implementation
      *   @param mouseEvent move event
      */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    /**
      *   @brief Mouse press event implementation
      *   @param mouseEvent mouse press event
      */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    /**
      *   @brief Move currentItem
      *   @param x new mouse center x coordinate
      *   @param y new mouse center y coordinate
      *   @remark does nothing if currentItem is nullptr
      */
    void MoveCurrentLevelItem(float x, float y);

    /**
      *   @brief Insert LevelItem
      *   On the first click this
      *   creates a new currentItem and on the second click currentItem is
      *   added to levelItems. This is just basically a wrapper method
      *   @param x mouse center x coordinate
      *   @param y mouse center y coordinate
      */
    void InsertLevelItem(float x, float y);


  private:

    /**
      *   @brief This checks that level name is valid (has correct extension)
      *   @param levelName to be validated
      *   @return true if levelName is valid, otherwise false
      */
    bool ValidateLevelName(const QString &levelName) const;

    /**
      *   @brief Connect LevelItem to previous one in x dimension
      *   @param x mouse x coordinate
      *   @param y mouse y coordinate
      *   @param width LevelItem width
      *   @return adjusted x coordinate, left coordinate, 0.f if not found matching previous item
      */
    float ConnectLevelItemX(float x, float y, float width);

    /**
      *   @brief Connect LevelItem to previous one in y dimension
      *   @param x mouse x coordinate
      *   @param y mouse y coordinate
      *   @return adjusted y coordinate, upper edge, 0.f if not found matching previous item
      */
    float ConnectLevelItemY(float x, float y, float height);


    std::deque<LevelItem*> levelItems; // use deque to push items front
    LevelItem *currentItem = nullptr;
    RectMap rectMap;

};
