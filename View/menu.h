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
  [[nodiscard]] QPushButton* GetLeftArrowButton() const;
  [[nodiscard]] QPushButton* GetRightArrowButton() const;
  [[nodiscard]] QPushButton* GetBackButton() const;
  [[nodiscard]] QPushButton* GetRestartButton() const;
  [[nodiscard]] QPushButton* GetResumeButton() const;
  [[nodiscard]] QPushButton* GetMenuButton() const;

  void MainMenu();
  void Pause();

 private:
  void SetObjectsNames();
  void Settings();
  Ui::Menu* ui;
};
#endif // MENU_H
