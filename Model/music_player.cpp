#include "music_player.h"

MusicPlayer::MusicPlayer()
    : main_player_(std::make_shared<QMediaPlayer>()),
      main_playlist_(std::make_shared<QMediaPlaylist>(main_player_.get())),
      button_sound_(std::make_shared<QMediaPlayer>()) {
  main_player_->setPlaylist(main_playlist_.get());

  main_playlist_->addMedia(QUrl("qrc:resources/sounds/menu_music.mp3"));
  main_playlist_->addMedia(QUrl("qrc:resources/sounds/game_music.mp3"));
  main_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  SetSound(button_sound_.get(), "qrc:resources/sounds/button_click.mp3");

  SetVolume(100);
  main_player_->play();
}

void MusicPlayer::SetVolume(int volume) {
  main_player_->setVolume(volume);
  button_sound_->setVolume(volume);
}

void MusicPlayer::StartMenuMusic() {
  main_playlist_->setCurrentIndex(kMenuMusic);
  main_player_->play();
}

void MusicPlayer::StartGameMusic() {
  main_playlist_->setCurrentIndex(kGameMusic);
  main_player_->play();
}

void MusicPlayer::PlayButtonSound() {
  button_sound_->play();
}

void MusicPlayer::SetSound(QMediaPlayer* player, const QString& path) {
  auto playlist = std::make_shared<QMediaPlaylist>();
  playlist->addMedia(QUrl(path));
  playlist->setCurrentIndex(0);

  player->setPlaylist(playlist.get());
  player->playlist()->setCurrentIndex(0);
  playlists_.push_back(std::move(playlist));
}

MusicPlayer::~MusicPlayer() {
  main_player_->stop();
  button_sound_->stop();
}

void MusicPlayer::Pause() {
  if (main_player_->state() == QMediaPlayer::PlayingState) {
    main_player_->pause();
  }
  if (button_sound_->state() == QMediaPlayer::PlayingState) {
    button_sound_->pause();
  }
}

void MusicPlayer::Resume() {
  if (main_player_->state() == QMediaPlayer::PausedState) {
    main_player_->play();
  }

  if (button_sound_->state() == QMediaPlayer::PausedState) {
    button_sound_->play();
  }
}
