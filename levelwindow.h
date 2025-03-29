#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QString>
#include <SFML/Audio.hpp>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "inputhandler.h"

class LevelWindow : public QMainWindow
{
    Q_OBJECT

public:
    LevelWindow(QWidget *parent = nullptr);
    void playSong(QPushButton *item); // Play song when button is clicked

private:
    // Layout and UI
    QVBoxLayout *layout;
    QLabel *title;
    QPushButton *levelButton1;
    QPushButton *levelButton2;
    QPushButton *levelButton3;

    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *restartButton;

    // Music
    QMap<QPushButton *, QString> songPaths;
    QString currentSongPath;
    sf::Music sfmlMusicPlayer; // For SFML-based playback
    QMediaPlayer *musicPlayer; // For Qt-based playback
    QAudioOutput *audioOutput;

    // Game window
    InputHandler *gameWindow = nullptr;

    // Logic
    void playPreview(QPushButton *button);
    void playFullSong(QPushButton *button);
    void pausePlayback();
    void stopPlayback();
    void restartPlayback();
};

#endif // LEVELWINDOW_H
