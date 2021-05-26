#ifndef VIEW_RESULT_WINDOW_H_
#define VIEW_RESULT_WINDOW_H_

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

  void LoadStyleSheets();

 private:
  void ConnectButtons();
  void SetObjetsNames();
  Ui::ResultWindow* ui;
  Size size_;
};
#endif  // VIEW_RESULT_WINDOW_H_
