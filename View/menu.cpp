#include <QFile>

#include "menu.h"
#include "./ui_menu.h"

Menu::Menu(QWidget* parent)
    : QWidget(parent), ui(new Ui::Menu) {
  ui->setupUi(this);
  setMinimumSize(QSize(500, 500));
  SetObjectsNames();
  LoadStyleSheet();
  connect(ui->settings, &QPushButton::released, this, &Menu::Settings);
  connect(ui->back_to_main_window,
          &QPushButton::released,
          this,
          &Menu::MainMenu);
}

void Menu::SetObjectsNames() {
  ui->widget->setObjectName(QObject::tr("background"));
  ui->play->setObjectName(QObject::tr("play"));
  ui->exit->setObjectName(QObject::tr("exit"));
  ui->settings->setObjectName(QObject::tr("settings"));
  ui->left_arrow->setObjectName(QObject::tr("left_arrow"));
  ui->right_arrow->setObjectName(QObject::tr("right_arrow"));
  ui->back_to_main_window->setObjectName(QObject::tr("back_to_main_window"));
  ui->restart->setObjectName(QObject::tr("restart"));
  ui->resume->setObjectName(QObject::tr("resume"));
  ui->menu->setObjectName(QObject::tr("menu"));
  ui->sound->setObjectName(QObject::tr("sound-on"));
  ui->sound_on_pause->setObjectName(QObject::tr("sound-on"));
  ui->cur_lang->setObjectName(QObject::tr("lang"));
}

void Menu::LoadStyleSheet() {
  QFile file(":resourses/buttons.qss");
  file.open(QFile::ReadOnly);
  QString stylesheet = file.readAll();
  setStyleSheet(stylesheet);
}

Menu::~Menu() {
  delete ui;
}

QPushButton* Menu::GetPlayButton() const {
  return ui->play;
}

QPushButton* Menu::GetExitButton() const {
  return ui->exit;
}

QPushButton* Menu::GetSettingsButton() const {
  return ui->settings;
}

void Menu::Pause() {
  ui->widget->setCurrentIndex(MenuPageIndex::kPause);
}

void Menu::Settings() {
  ui->widget->setCurrentIndex(MenuPageIndex::kSettings);
}

void Menu::MainMenu() {
  ui->widget->setCurrentIndex(MenuPageIndex::kStartMenu);
}

QPushButton* Menu::GetLeftArrowButton() const {
  return ui->left_arrow;
}

QPushButton* Menu::GetRightArrowButton() const {
  return ui->right_arrow;
}

QPushButton* Menu::GetBackButton() const {
  return ui->back_to_main_window;
}

QPushButton* Menu::GetRestartButton() const {
  return ui->restart;
}

QPushButton* Menu::GetResumeButton() const {
  return ui->resume;
}

QPushButton* Menu::GetMenuButton() const {
  return ui->menu;
}

QPushButton* Menu::GetSoundButton() const {
  return ui->sound;
}

QPushButton* Menu::GetSoundOnPauseButton() const {
  return ui->sound_on_pause;
}





