#include "menu.h"
#include "./ui_menu.h"

Menu::Menu(QWidget* parent)
    : QWidget(parent), ui(new Ui::Menu) {
  ui->setupUi(this);
  ui->widget->setStyleSheet(
      "QWidget {background-image: url(:images/menu/background/background.png) }");
  play_ = new QPushButton("Play");
  ui->buttons->layout()->addWidget(play_);
}

Menu::~Menu() {
  delete ui;
}

QPushButton* Menu::GetPlay() const {
  return play_;
}

