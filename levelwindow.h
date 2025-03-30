/**
 * @file levelwindow.cpp
 * @author Julie Vo
 * @date 29 March 2012
 * @brief File containing level window functions.
 *
 */
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
#include "mainwindow.h"

/**
 * @brief A window that represents a level selection screen with music control.
 *
 * The LevelWindow class provides functionality for selecting a game level,
 * playing a preview of the song, and controlling music playback with
 * play, pause, stop, and restart options.
 *
 * @author Julie Vo
 */

class LevelWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the LevelWindow class.
     *
     * Initializes the layout, buttons, and connects necessary signals and slots.
     *
     * @param parent The parent widget that owns this window.
     */
    explicit LevelWindow(QWidget *parent = nullptr);
    /**
     * @brief Plays the song associated with the button when clicked.
     *
     * This function will play the full song if the song is not already playing,
     * or start a new song if another song is playing.
     *
     * @param item The button that corresponds to the song to be played.
     */
    void playSong(QPushButton *item); // Play song when button is clicked
    QString username;

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
    QPushButton *backButton;

    // Music
    QMap<QPushButton *, QString> songPaths;
    QString currentSongPath;
    sf::Music sfmlMusicPlayer; // For SFML-based playback
    QMediaPlayer *musicPlayer; // For Qt-based playback
    QAudioOutput *audioOutput;

    // Game window
    InputHandler *gameWindow = nullptr;

    // Music playback logic functions
    /**
     * @brief Plays the preview of the song when a button is clicked.
     *
     * This function will play a short preview of the song associated with the button.
     *
     * @param button The button clicked to play the preview.
     */
    void playPreview(QPushButton *button);
    /**
     * @brief Plays the full song when a button is clicked.
     *
     * This function starts playback of the entire song associated with the button.
     *
     * @param button The button clicked to play the full song.
     */
    void playFullSong(QPushButton *button);
    /**
     * @brief Pauses the current song playback.
     *
     * This function will pause the playback of the current song.
     */
    void pausePlayback();
    /**
     * @brief Stops the current song playback.
     *
     * This function will stop the current song, resetting it to the beginning.
     */
    void stopPlayback();
    /**
     * @brief Restarts the current song from the beginning.
     *
     * This function will stop and play the song from the start.
     */
    void restartPlayback();
};

#endif // LEVELWINDOW_H
