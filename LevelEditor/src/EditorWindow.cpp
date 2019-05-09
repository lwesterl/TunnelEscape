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
  CreateToolbar();
}

// Deconstructor
EditorWindow::~EditorWindow() {
  delete toolbar;
  delete view;
  delete editor;
}



// Create menu, private method
void EditorWindow::CreateMenu() {
  QMenu *fileOptions;
  fileOptions = menuBar()->addMenu("File");
  QAction *save = new QAction("Save", this);
  connect(save, SIGNAL(triggered()), this, SLOT(SaveSlot()) );
  fileOptions->addAction(save);
  QAction *load = new QAction("Load", this);
  connect(load, SIGNAL(triggered()), this, SLOT(LoadSlot()) );
  fileOptions->addAction(load);
  // todo map editor actions for these

  QMenu *elementOptions;
  elementOptions = menuBar()->addMenu("Elements");
  for (int i = static_cast<int>(AssetManager::ImageAssets::BlackGround);
           i < static_cast<int>(AssetManager::ImageAssets::LightSky); i++) {
    QAction *action = new QAction(
      QIcon( *AssetManager::getPixmap(static_cast<AssetManager::ImageAssets>(i))),
             QString::fromStdString(AssetManager::getImageAssetStr(static_cast<AssetManager::ImageAssets>(i))),
             this);
    action->setData(QVariant(i));
    connect(action, SIGNAL(triggered()), this, SLOT(ChangeEditorImageSlot()) );
    elementOptions->addAction(action);
  }

  QMenu *settings;
  settings = menuBar()->addMenu("Settings");

}

void EditorWindow::CreateToolbar() {
  toolbar = new QToolBar();
  addToolBar(toolbar);
  const char names[][8] = { "Preview", "Insert", "Remove" };
  // make sure that EditorMode::RemoveMode equals 2
  for (int i = static_cast<int>(EditorMode::PreviewMode); i <= static_cast<int>(EditorMode::RemoveMode); i++) {
    toolbarButtons[i] = new QPushButton(names[i], toolbar); // toolbar should now also delete memory allocated for buttons
    toolbarButtons[i]->setProperty(PushButtonPropertyName, QVariant(i));
    toolbarButtons[i]->setCheckable(true);
    connect(toolbarButtons[i], SIGNAL(clicked()), this, SLOT(SetEditorModeSlot()) );
    toolbar->addWidget(toolbarButtons[i]);
  }
  Editor::CurrentEditorMode = EditorMode::PreviewMode;
  toolbarButtons[0]->setChecked(true);
}


// Save level to file, private slot
void EditorWindow::SaveSlot() {
  QFileDialog save(this);
  save.setAcceptMode(QFileDialog::AcceptSave);
  save.setFileMode(QFileDialog::AnyFile);
  save.setNameFilter(tr(LevelNameExtensionPattern));
  if (save.exec()) {
    QStringList selectedFiles = save.selectedFiles();
    if (editor->saveLevel(selectedFiles[0])) {
      QMessageBox::information(this, "Information", "Level successfully saved");
    } else QMessageBox::warning(this, "Warning", "Level saving failed");
  }
}

// Load old level, private slot
void EditorWindow::LoadSlot() {
  QMessageBox::warning(this, "Warning", "Loading level will erase current content");
  QFileDialog load(this);
  load.setAcceptMode(QFileDialog::AcceptOpen);
  load.setFileMode(QFileDialog::ExistingFile);
  load.setNameFilter(tr(LevelNameExtensionPattern));
  if (load.exec()) {
    QStringList selectedFiles = load.selectedFiles();
    if (editor->loadLevel(selectedFiles[0])) {
      QMessageBox::information(this, "Information", "Level successfully loaded");
    } else QMessageBox::warning(this, "Warning", "Level loading failed");
  }
}

// Change image asset value in Editor, private slot
void EditorWindow::ChangeEditorImageSlot() {
  QAction *action = qobject_cast<QAction*>(sender());
  if (action) {
    AssetManager::ImageAssets imageAsset = qvariant_cast<AssetManager::ImageAssets>(action->data());
    Editor::LevelItemImageAsset = imageAsset;
    editor->removeCurrentLevelItem(); // remove so that old asset isn't stored
  }
}

// Change editor mode, private slot
void EditorWindow::SetEditorModeSlot() {
  QPushButton *button = qobject_cast<QPushButton*>(sender());
  if (button) {
    EditorMode editorMode = qvariant_cast<EditorMode>(button->property(PushButtonPropertyName));
    Editor::CurrentEditorMode = editorMode;
    editor->removeCurrentLevelItem(); // remove so that old asset isn't stored
    // set other toolbarButtons not checked
    for (int i = static_cast<int>(EditorMode::PreviewMode); i <= static_cast<int>(EditorMode::RemoveMode); i++) {
      if (toolbarButtons[i] != button) {
        toolbarButtons[i]->setChecked(false);
      }
    }
  }
}
