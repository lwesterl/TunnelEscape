/**
  *   @file ComboBoxAction.cpp
  *   @author Lauri Westerholm
  *   @brief Source for ComboBoxAction
  */


#include "../include/ComboBoxAction.hpp"



// Constructor
ComboBoxAction::ComboBoxAction(const QString &info, QWidget *parent): QWidgetAction(parent)
{
  // Create a new QWidget
  QWidget *default_widget = new QWidget(parent);
  // create the combobox
  combobox = new QComboBox(default_widget);

  // create a vertical layout
  QVBoxLayout *layout = new QVBoxLayout(default_widget);
  layout->addWidget(new QLabel(info, default_widget));
  layout->addWidget(combobox);

  // set the layout
  default_widget->setLayout(layout);
  setDefaultWidget(default_widget);
}

// A small wrapper to access combobox index value
int ComboBoxAction::getComboIndex() const { return combobox->currentIndex(); }

/*  Change item text */
void ComboBoxAction::setItemText(const int index, const QString text) {
  if (index < combobox->count() && index > -1) combobox->setItemText(index, text);
}

/*  Add a new item */
void ComboBoxAction::addItem(const QString &text) { combobox->addItem(text); }


// start of namespace ComboBox, end of class ComboboxAction
namespace ComboBox {

  // This is a bit fancy bit manipulation based implementation, saves two if else statements
  void setConnectMode(const ConnectMode connectMode) {
    Editor::ConnectToPreviousItemsX = false;
    Editor::ConnectToPreviousItemsY = false;
    const int connect = static_cast<int>(connectMode);
    if ((connect & static_cast<int>(ConnectMode::XConnect)) == static_cast<int>(ConnectMode::XConnect)) {
      Editor::ConnectToPreviousItemsX = true;
    }
    if ((connect & static_cast<int>(ConnectMode::YConnect)) == static_cast<int>(ConnectMode::YConnect)) {
      Editor::ConnectToPreviousItemsY = true;
    }
  }

  // map from ConnectModes to QStrings
  std::map<const ConnectMode, const QString> ConnectModeToStr =
  {
    { ConnectMode::NoConnect, "Don't connect (default)" },
    { ConnectMode::XConnect, "Connect in x dimension" },
    { ConnectMode::YConnect, "Connect in y dimension" },
    { ConnectMode::XYConnect, "Connect both x and y dimensions" }
  };
} // end of namespace ComboBox
