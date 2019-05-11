/**
  *   @file ComboBoxAction.hpp
  *   @author Lauri Westerholm
  *   @brief Header for ComboBoxAction class
  */

#pragma once
#include "Editor.hpp"


#include <QObject>
#include <QWidget>
#include <QWidgetAction>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <map>


/**
  *   @class ComboBoxAction
  *   @brief Implements own QComboBox
  *   @details This class implements a QComboBox which can be added to a menuBar
  */

class ComboBoxAction: public QWidgetAction {
  Q_OBJECT

  public:

  /**
    *   @brief Constructor for ComboboxAction
    *   @param info String which is added to info label
    *   @param QWidget parent which handles object deletion
    */
    ComboBoxAction(const QString &info, QWidget *parent=nullptr);

  /**
    *   @brief Get combobox index
    *   @return Returns combobox index
    *   @details Calls QComboBox currentIndex()
    */
    int getComboIndex() const;

  /**
    *   @brief Set Item text
    *   @details This allows set other text than yes / no which are the defaults
    *   @param index Index of the item which text is changed
    *   @param text New item text
    */
    void setItemText(const int index, const QString text);

  /**
    *   @brief Add new item to the combobox
    *   @param text Item text
    */
    void addItem(const QString &text);

  private:
    QComboBox *combobox;

};

/**
  *   @namespace ComboBox
  *   @brief Contains ComboBoxAction related data structures
  */
namespace ComboBox {

  /**
    *   @enum ConnectMode
    *   @brief Contains  constants for all Editor connect modes
    */
  enum class ConnectMode: int {
    NoConnect = 0, /**< No connections to previous LevelItems */
    XConnect = 1, /**< Connections in x dimension */
    YConnect = 2, /**< Connections in y dimension */
    XYConnect = 3 /**< Connections in both x and y dimensions */
  };

  /**< Map from ConnectMode to QString constant */
  extern std::map<const ConnectMode, const QString> ConnectModeToStr;

  /**
    *   @brief Set correct connect mode to Editor
    *   @param connectMode new ConnectMode
    */
  void setConnectMode(const ConnectMode connectMode);
} // end of namespace ComboBox
