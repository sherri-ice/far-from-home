#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include "../Model/point.h"
#include "../Model/size.h"

enum ResultState {
  kFound,
  kNotFound
};

QT_BEGIN_NAMESPACE
namespace Ui { class ResultWindow; }
QT_END_NAMESPACE

class ResultWindow : public QDialog {
 Q_OBJECT

 public:
  explicit ResultWindow(QWidget* parent = nullptr);
  ~ResultWindow() override;

  void Show(bool is_found);
  bool GetUserAnswer();

 private:
  void ConnectButtons();
  Ui::ResultWindow* ui;
  Size size_;
};
#endif // RESULTWINDOW_H
