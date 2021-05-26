#ifndef VIEW_WIN_WINDOW_H_
#define VIEW_WIN_WINDOW_H_

#include <QWidget>
#include <QPushButton>
#include "../Model/constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WinWindow; }
QT_END_NAMESPACE

class WinWindow : public QWidget {
  Q_OBJECT

 public:
  explicit WinWindow(QWidget* parent = nullptr);
  ~WinWindow() override;

  [[nodiscard]] QPushButton* GetMenuButton() const;

  void LoadStyleSheets();

 private:
  void SetObjectsNames();
  Ui::WinWindow* ui;
};
#endif  // VIEW_WIN_WINDOW_H_
