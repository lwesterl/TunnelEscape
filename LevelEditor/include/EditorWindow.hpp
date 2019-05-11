/**
  *   @file EditorWindow.hpp
  *   @author Lauri Westerholm
  *   @brief Contains EditorWindow
  */

#pragma once
#include "Editor.hpp"
#include "AssetManager.hpp"
#include "ComboBoxAction.hpp"
#include "RectMap.hpp" // contains NON_COPYABLE macro

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
#include <QKeyEvent>
#include <QApplication>

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
    static bool ControlPressed; /**< tells whether control is currently pressed */

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

  protected:

    /**
      *   @brief Implementation for key press events
      *   @param event tells event info
      */
    void keyPressEvent(QKeyEvent *event) override;

    /**
      *   @brief Key release event implementation
      *   @param event tells event info
      */
    void keyReleaseEvent(QKeyEvent *event) override;

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
        *   @brief Settings saved slot
        */
      void SettingsSavedSlot();

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

      /**
        *   @brief Slot for clearing all LevelItems
        *   @details toolbarButtons[3] is connected to this slot
        */
      void ClearLevelItemsSlot();

  private:
    NON_COPYABLE(EditorWindow); /**< Make non-copyable */

    /**
      *   @brief Create Menu for level editor
      */
    void CreateMenu();

    /**
      *   @brief Create Toolbar for level editor
      */
    void CreateToolbar();

    /**
      *   @brief Check if control is pressed
      */
    void CheckControlModifiers();



    ComboBoxAction *comboBoxAction;
    QToolBar *toolbar;
    QPushButton* toolbarButtons[4];
    QGraphicsView *view;
    Editor *editor;

};
