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
  [[nodiscard]] QPushButton* GetPlay() const;

 private:
  Ui::Menu* ui;
  QPushButton* play_;
};
#endif // MENU_H
