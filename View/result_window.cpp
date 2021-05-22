#include "result_window.h"
#include "./ui_result_window.h"
#include "../Model/constants.h"

ResultWindow::ResultWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::ResultWindow) {
  ui->setupUi(this);
  ConnectButtons();
}

ResultWindow::~ResultWindow() {
  delete ui;
}

void ResultWindow::ConnectButtons() {
  connect(ui->okay_button, &QPushButton::released, this, &ResultWindow::close);
  connect(ui->cancel_button, &QPushButton::released, this, &ResultWindow::close);
}

void ResultWindow::Show(bool is_found) {
  if (is_found) {
    ui->widget->setCurrentIndex(ResultState::kFound);
  } else {
    ui->widget->setCurrentIndex(ResultState::kNotFound);
  }
  show();
}

