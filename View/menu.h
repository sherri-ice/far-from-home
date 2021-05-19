#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <memory>

enum MenuPageIndex {
  kStartMenu,
  kSettings,
  kPause
};

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
  [[nodiscard]] QPushButton* GetExitButton() const;
  [[nodiscard]] QPushButton* GetSettingsButton() const;

  void Pause();

 private:
  void SetObjectsNames();
  void Settings();
  void MainMenu();
  Ui::Menu* ui;
};
#endif // MENU_H
