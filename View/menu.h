#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QWidget {
 Q_OBJECT

 public:
  explicit Menu(QWidget* parent = nullptr);
  ~Menu() override;
  void LoadStyleSheet();
  [[nodiscard]] QPushButton* GetPlayButton() const;

 private:
  Ui::Menu* ui;
};
#endif // MENU_H
