/**
  *   @file EditorWindow.cpp
  *   @author Lauri Westerholm
  *   @brief source code for EditorWindow
  */


#include "../include/EditorWindow.hpp"

// Init ControlPressed
bool EditorWindow::ControlPressed = false;


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
  delete comboBoxAction;
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
  comboBoxAction = new ComboBoxAction("Connect to previous items:", settings);
  for (int i = static_cast<int>(ComboBox::ConnectMode::NoConnect); i <= static_cast<int>(ComboBox::ConnectMode::XYConnect); i++) {
    comboBoxAction->addItem(ComboBox::ConnectModeToStr[static_cast<ComboBox::ConnectMode>(i)]);
  }
  settings->addAction(comboBoxAction);
  QAction *saveSettings = new QAction("Save settings", this);
  settings->addAction(saveSettings);
  connect(saveSettings, SIGNAL(triggered()), this, SLOT(SettingsSavedSlot()) );
}

// Create toolbar
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
  // create one extra buttons to clear whole level
  toolbarButtons[3] = new QPushButton("Clear all", toolbar);
  connect(toolbarButtons[3], SIGNAL(clicked()), this, SLOT(ClearLevelItemsSlot()) );
  toolbar->addSeparator();
  toolbar->addWidget(toolbarButtons[3]);
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
  CheckControlModifiers();
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
  CheckControlModifiers();
}

// Save settings, private slot
void EditorWindow::SettingsSavedSlot() {
  int index = comboBoxAction->getComboIndex();
  ComboBox::setConnectMode(static_cast<ComboBox::ConnectMode> (index));
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

// Clear whole level, private slot
void EditorWindow::ClearLevelItemsSlot() {
  editor->clearLevelItems();
}

// Key press implementation, protected
void EditorWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Control) EditorWindow::ControlPressed = true;
  else if (event->key() == Qt::Key_S && EditorWindow::ControlPressed) SaveSlot();
  else if (event->key() == Qt::Key_O && EditorWindow::ControlPressed) LoadSlot();
  else if (event->key() == Qt::Key_Q && EditorWindow::ControlPressed) QCoreApplication::quit();
  else if (event->key() == Qt::Key_Backspace) editor->removeCurrentLevelItem();
}

// Key release implementation, protected
void EditorWindow::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Control) EditorWindow::ControlPressed = false;
}

// Check whether control is pressed, private method
void EditorWindow::CheckControlModifiers() {
  Qt::KeyboardModifiers modifiers = QApplication::queryKeyboardModifiers();
  if ((modifiers & Qt::ControlModifier) == Qt::ControlModifier) {
    EditorWindow::ControlPressed = true;
  } else EditorWindow::ControlPressed = false;
}
