#include <QFile>
#include "menu.h"
#include "./ui_menu.h"
#include <QDebug>

Menu::Menu(QWidget* parent)
    : QWidget(parent), ui(new Ui::Menu) {
  ui->setupUi(this);
  ui->widget->setObjectName(QObject::tr("background"));
  ui->play->setObjectName(QObject::tr("play"));
  LoadStyleSheet();
  // ui->play->setIcon(QIcon(QPixmap(":images/menu/buttons/play.png")));
  // ui->play->setIconSize(QPixmap(":images/menu/buttons/play.png").rect().size());
  // ui->buttons->layout()->addWidget(play_);
}

void Menu::LoadStyleSheet() {
  QFile file(":resourses/buttons.qss");
  file.open(QFile::ReadOnly);
  QString stylesheet = file.readAll();
  setStyleSheet(stylesheet);
}

Menu::~Menu() {
  delete ui;
}

QPushButton* Menu::GetPlayButton() const {
  return ui->play;
}



