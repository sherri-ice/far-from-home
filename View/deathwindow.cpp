#include <QFile>

#include "deathwindow.h"
#include "./ui_deathwindow.h"

DeathWindow::DeathWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::DeathWindow) {
  ui->setupUi(this);
  SetObjectsNames();
  LoadStyleSheets();
  setVisible(false);
  resize(constants::kGameWidth, constants::kGameHeight);
}

DeathWindow::~DeathWindow() {
  delete ui;
}

void DeathWindow::SetObjectsNames() {
  ui->widget->setObjectName(QObject::tr("death"));
  ui->replay->setObjectName(QObject::tr("restart"));
  ui->menu->setObjectName(QObject::tr("menu"));
}

void DeathWindow::LoadStyleSheets() {
  QFile file(":resourses/buttons.qss");
  file.open(QFile::ReadOnly);
  QString stylesheet = file.readAll();
  setStyleSheet(stylesheet);
}

QPushButton* DeathWindow::GetReplayButton() const {
  return ui->replay;
}

QPushButton* DeathWindow::GetMenuButton() const {
  return ui->menu;
}
