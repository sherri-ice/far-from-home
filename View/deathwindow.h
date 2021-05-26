#ifndef VIEW_DEATHWINDOW_H_
#define VIEW_DEATHWINDOW_H_

#include <QWidget>
#include <QPushButton>
#include "../Model/constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DeathWindow; }
QT_END_NAMESPACE

class DeathWindow : public QWidget {
  Q_OBJECT

 public:
  explicit DeathWindow(QWidget* parent = nullptr);
  ~DeathWindow() override;

  [[nodiscard]] QPushButton* GetReplayButton() const;
  [[nodiscard]] QPushButton* GetMenuButton() const;

  void LoadStyleSheets();

 private:
  Ui::DeathWindow* ui;
  void SetObjectsNames();
};
#endif  // VIEW_DEATHWINDOW_H_
