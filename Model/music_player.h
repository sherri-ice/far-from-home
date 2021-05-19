#ifndef MODEL_MUSIC_PLAYER_H
#define MODEL_MUSIC_PLAYER_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <memory>
#include <vector>
#include <utility>
// #include "GameObject/abstract_projectile.h"

enum MainMusic {
  kMenuMusic,
  kGameMusic,
};

class MusicPlayer {
 public:
  MusicPlayer();
  ~MusicPlayer();
  void SetVolume(int volume);

  void StartMenuMusic();
  void StartGameMusic();
  void PlayButtonSound();

  void Pause();
  void Resume();

 private:
  void SetSound(QMediaPlayer* player, const QString& path);
  std::shared_ptr<QMediaPlayer> main_player_;
  std::shared_ptr<QMediaPlaylist> main_playlist_;

  std::shared_ptr<QMediaPlayer> button_sound_;
  std::vector<std::shared_ptr<QMediaPlaylist>> playlists_;
};

#endif // MODEL_MUSIC_PLAYER_H
