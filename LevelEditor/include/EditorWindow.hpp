/**
  *   @file EditorWindow.hpp
  *   @author Lauri Westerholm
  *   @brief Contains EditorWindow
  */

#pragma once
#include "Editor.hpp"
#include "AssetManager.hpp"

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsView>
#include <QVBoxLayout>

/**
  *   @class EditorWindow
  *   @brief This class handles the main window and UI of LevelEditor
  */
class EditorWindow: public QMainWindow {
  Q_OBJECT

  public:

    /**
      *   @brief Constructor
      *   @param parent QWidget parant, should be null because this is the main
      *   window
      */
    EditorWindow(QWidget *parent=0);

    /**
      *   @brief Deconstructor
      */
    ~EditorWindow();

  private:

    /**
      *   @brief Create Menu for level editor
      */
    void CreateMenu();



    QGraphicsView *view;
    Editor *editor;


};
