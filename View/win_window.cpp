#include "win_window.h"
#include "./ui_winwindow.h"

#include <QFile>

WinWindow::WinWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::WinWindow) {
  ui->setupUi(this);
  SetObjectsNames();
  LoadStyleSheets();
  setVisible(false);
  resize(constants::kGameWidth, constants::kGameHeight);
}

WinWindow::~WinWindow() {
  delete ui;
}

void WinWindow::SetObjectsNames() {
  ui->widget->setObjectName(QObject::tr("win"));
  ui->Menu->setObjectName(QObject::tr("menu"));
}

QPushButton* WinWindow::GetMenuButton() const {
  return ui->Menu;
}

void WinWindow::LoadStyleSheets() {
  QFile file(":resourses/buttons.qss");
  file.open(QFile::ReadOnly);
  QString stylesheet = file.readAll();
  setStyleSheet(stylesheet);
}

