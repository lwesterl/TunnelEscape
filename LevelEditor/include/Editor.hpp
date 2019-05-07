/**
  *   @file Editor.hpp
  *   @author Lauri Westerholm
  *   @brief Contains Editor class
  */

#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>


/**
  *   @class Editor
  *   @brief Handles the level editing
  */

class Editor: public QGraphicsScene {
  Q_OBJECT

  public:
    static const int ScreenWidth = 20000; /**< Screen width */
    static const int ScreenHeight = 10000; /**< Screen height */

    /**
      *   @brief Constructor
      *   @param parent paren QObject
      */
    Editor(QObject *parent);

    /**
      *   @brief Deconstructor
      */
    virtual ~Editor();


  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;


  private:


};
