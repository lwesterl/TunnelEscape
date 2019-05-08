/**
  *   @file EditorWindow.cpp
  *   @author Lauri Westerholm
  *   @brief source code for EditorWindow
  */


#include "../include/EditorWindow.hpp"


// Constructor
EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {

  setWindowTitle("Level editor");

  // set central widget
  QWidget *widget = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(widget);
  view = new QGraphicsView(widget);
  widget->setLayout(layout);
  layout->addWidget(view);
  setCentralWidget(widget);
  editor = new Editor(widget);
  view->setScene(editor);
  view->setMouseTracking(true);

  CreateMenu();

}

// Deconstructor
EditorWindow::~EditorWindow() {
  delete view;
  delete editor;
}



// Create menu, private method
void EditorWindow::CreateMenu() {
  QMenu *fileOptions;
  fileOptions = menuBar()->addMenu("File");
  fileOptions->addAction(new QAction("Save", this));
  fileOptions->addAction(new QAction("Load", this));
  // todo map editor actions for these

  QMenu *elementOptions;
  elementOptions = menuBar()->addMenu("Elements");
  for (int i = static_cast<int>(AssetManager::ImageAssets::BlackGround);
           i < static_cast<int>(AssetManager::ImageAssets::LightSky); i++) {
    elementOptions->addAction(new QAction(
      QIcon( *AssetManager::getPixmap(static_cast<AssetManager::ImageAssets>(i))),
             QString::fromStdString(AssetManager::getImageAssetStr(static_cast<AssetManager::ImageAssets>(i)))
           ));
  }

  QMenu *settings;
  settings = menuBar()->addMenu("Settings");

}
