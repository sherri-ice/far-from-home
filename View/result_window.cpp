#include "result_window.h"
#include "./ui_result_window.h"
#include "../Model/constants.h"

#include <QDebug>

ResultWindow::ResultWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::ResultWindow) {
  ui->setupUi(this);
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
  qDebug() << is_found;
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


