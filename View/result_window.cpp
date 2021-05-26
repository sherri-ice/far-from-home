#include "result_window.h"
#include "./ui_result_window.h"
#include "../Model/constants.h"
#include <QFile>

ResultWindow::ResultWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::ResultWindow) {
  ui->setupUi(this);
  SetObjetsNames();
  LoadStyleSheets();
  ConnectButtons();
}

ResultWindow::~ResultWindow() {
  delete ui;
}

void ResultWindow::ConnectButtons() {
  connect(ui->okay_button, &QPushButton::released, this, [this] {
    reject();
  });
  connect(ui->cancel_button, &QPushButton::released, this, [this] {
    reject();
  });
  connect(ui->send_button, &QPushButton::released, this, [this] {
    accept();
  });
}

void ResultWindow::Show(bool is_found) {
  if (is_found) {
    ui->widget->setCurrentIndex(ResultState::kFound);
  } else {
    ui->widget->setCurrentIndex(ResultState::kNotFound);
  }

  exec();
}

bool ResultWindow::GetUserAnswer() {
  return (result() == true);
}

void ResultWindow::LoadStyleSheets() {
  QFile file(":resourses/buttons.qss");
  file.open(QFile::ReadOnly);
  QString stylesheet = file.readAll();
  setStyleSheet(stylesheet);
}


void ResultWindow::SetObjetsNames() {
  setObjectName(QObject::tr("background"));
  ui->no_text->setObjectName(QObject::tr("no"));
  ui->yes_text->setObjectName(QObject::tr("yes"));
  ui->okay_button->setObjectName(QObject::tr("cancel"));
  ui->cancel_button->setObjectName(QObject::tr("cancel"));
  ui->send_button->setObjectName(QObject::tr("send"));
}


