/**
  *   @file Editor.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for Editor class
  */

#include "../include/Editor.hpp"

// Consructor
Editor::Editor(QObject *parent): QGraphicsScene(parent) {
  setSceneRect(0, 0, Editor::ScreenWidth, Editor::ScreenHeight);
  addItem(new QGraphicsRectItem(0.f, 0.f, 100.f, 100.f));
}

// Deconstructor
Editor::~Editor() {}

// Mouse move event implementation, protected
void Editor::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  qDebug() << mouseEvent->scenePos();
}

// Mouse press event implementation, protected
void Editor::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  //qDebug() << mouseEvent->pos();
}

// Mouse release event implementation, protected
void Editor::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  //qDebug() << mouseEvent->pos();
}
