
/**
  *   @file main.cpp
  *   @author Lauri Westerholm
  *   @brief Contains main for LevelEditor program
  */



#include "../include/EditorWindow.hpp"
#include "../include/AssetManager.hpp"
#include <QApplication>

/**
  *   @brief Main for LevelEditor program
  *   @param args The number of command line arguments
  *   @param argv Command line arguments
  */

int main(int args, char *argv[])
{
  QApplication app(args, argv);
  AssetManager::INIT();
  EditorWindow editorWindow;
  editorWindow.resize(700,500);
  editorWindow.show();

  return app.exec();
  AssetManager::DELETE();
}
