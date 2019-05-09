/**
  *   @file EditorWindow.hpp
  *   @author Lauri Westerholm
  *   @brief Contains EditorWindow
  */

#pragma once
#include "Editor.hpp"
#include "AssetManager.hpp"

#include <QMainWindow>
#include <QObject>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QVariant>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QToolBar>
#include <QPushButton>

#ifndef QTMetaTypes
#define QTMetaTypes
// These should be declared only once
Q_DECLARE_METATYPE(AssetManager::ImageAssets)
Q_DECLARE_METATYPE(EditorMode);
#define PushButtonPropertyName "data" /**< used to store data using setProperty */
#endif

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

    private slots:

      /**
        *   @brief Save level
        */
      void SaveSlot();

      /**
        *   @brief Load level
        */
      void LoadSlot();

      /**
        *   @brief Slot which is used to change Editor LevelItemImageAsset
        *   @details Elements actions are connected to this slot
        */
      void ChangeEditorImageSlot();

      /**
        *   @brief Slot for setting editor mode
        *   @details toolbarButtons are connected to this slot
        */
      void SetEditorModeSlot();


  private:

    /**
      *   @brief Create Menu for level editor
      */
    void CreateMenu();

    /**
      *   @brief Create Toolbar for level editor
      */
    void CreateToolbar();



    QToolBar *toolbar;
    QPushButton* toolbarButtons[3];
    QGraphicsView *view;
    Editor *editor;

};
