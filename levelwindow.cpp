/**
 * @file levelwindow.cpp
 * @author Julie Vo
 * @date 29 March 2012
 * @brief File containing level window functions.
 *
 */
#include "levelwindow.h"
#include "inputhandler.h"
#include "mainwindow.h"
#include "user.h"
#include "userfactory.h"
#include <QSpacerItem>
#include <QSizePolicy>
#include <QTemporaryFile>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QMainWindow>

/**
 * @brief Constructor for the LevelWindow class.
 *
 * Initializes the window layout, buttons, and connects signals and slots for the music playback,
 * level selection, and transitions to the game window.
 *
 * @param parent The parent widget for the window.
 */
LevelWindow::LevelWindow(QWidget *parent) : QMainWindow(parent)
{
    // Retrieve user information
    QString username = this->username;
    UserFactory uf;
    User loginUser = uf.createUser(username);
    qDebug() << "(Level Window Check Top) Username:" << loginUser.getUsername();

    // Create a central widget and set it to the QMainWindow
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set central widget for the window

    // Create the layout for the central widget
    layout = new QVBoxLayout(centralWidget);

    setStyleSheet("background-color: #F5EFFF;");

    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    title = new QLabel("Select Level", this);
    title->setStyleSheet("QLabel { color: #924AEB; }");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

    levelButton1 = new QPushButton("Easy", this);
    levelButton2 = new QPushButton("Medium", this);
    levelButton3 = new QPushButton("Hard", this);
    backButton = new QPushButton("Back to Menu", this);

    QPushButton *levelButtons[] = {levelButton1, levelButton2, levelButton3};
    QString levelSongs[] = {":/audio/easysong.mp3", ":/audio/mediumsong.mp3", ":/audio/hardsong.mp3"};

    for (int i = 0; i < 3; i++)
    {
        QPushButton *button = levelButtons[i];
        layout->addWidget(button);
        button->setFixedSize(300, 50);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        songPaths[button] = levelSongs[i];

        connect(button, &QPushButton::pressed, this, [this, button]
                { playSong(button); });

        connect(button, &QPushButton::clicked, this, [this, button]() {
            QString username = this->username;
            UserFactory uf;
            User loginUser = uf.createUser(username);
            qDebug() << "(Level Window Check Later) Username:" << this->username;

            stopPlayback();

            QString level = button->text();
            if (gameWindow == nullptr) {
                gameWindow = new InputHandler(this->username);
            }
            connect(gameWindow, &InputHandler::backToMenu, this, [this]() {
                QString username = this->username;

                stopPlayback();
                LevelWindow *newMenu = new LevelWindow();
                newMenu->username = this->username;
                qDebug() << "(Level Window Check back) Username:" << newMenu->username;
                newMenu->show();
                this->close();
            });

            if (level == "Easy") gameWindow->launchEasyMode();
            else if (level == "Medium") gameWindow->launchMediumMode();
            else if (level == "Hard") gameWindow->launchHardMode();
            gameWindow->show();
            this->close();
        });
    }

    layout->setAlignment(Qt::AlignCenter);
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QFont titleFont("Helvetica", 50, QFont::Bold);
    title->setFont(titleFont);

    QFont buttonFont("Helvetica", 16, QFont::Light);
    levelButton1->setFont(buttonFont);
    levelButton2->setFont(buttonFont);
    levelButton3->setFont(buttonFont);
    backButton->setFont(buttonFont);

    QString buttonStyle = "QPushButton {"
                          "background-color: #E9A5F1;"
                          "border-radius: 15px;"
                          "color: white;"
                          "border: 2px solid #DD8DF5;"
                          "padding: 10px;"
                          "margin: 10px;"
                          "font-size: 16px;"
                          "font-weight: bold;"
                          "min-width: 300px;"
                          "min-height: 50px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #C68EFD;"
                          "border: 2px solid #924AEB;"
                          "}";

    levelButton1->setStyleSheet(buttonStyle);
    levelButton2->setStyleSheet(buttonStyle);
    levelButton3->setStyleSheet(buttonStyle);


    backButton->setFixedSize(200,40);
    layout->addWidget(backButton);
    backButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Align it to the center
    layout->setAlignment(backButton, Qt::AlignCenter);
    layout->addSpacerItem(new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed));
    backButton->setStyleSheet(QStringLiteral(
        "QPushButton {"
        "background-color: #E9A5F1;"
        "border-radius: 15px;"
        "color: white;"
        "border: 2px solid #DD8DF5;"
        "padding: 10px;"
        "margin: 10px;"
        "font-size: 16px;"
        "font-weight: bold;"
        "min-width: 200px;"
        "min-height: 40px;"
        "}"
        "QPushButton:hover {"
        "background-color: #C68EFD;"
        "border: 2px solid #924AEB;"
        "}"
        ));


    connect(backButton, &QPushButton::clicked, this, [this]() {
        stopPlayback();
        MainWindow *mainMenu = new MainWindow();
        mainMenu->username = this->username;
        mainMenu->show();
        this->close();
    });

    connect(pauseButton, &QPushButton::clicked, this, &LevelWindow::pausePlayback);
    connect(stopButton, &QPushButton::clicked, this, &LevelWindow::stopPlayback);
    connect(restartButton, &QPushButton::clicked, this, &LevelWindow::restartPlayback);

    // Initialize Qt music player
    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
}

/**
 * @brief Plays the selected song when a button is clicked.
 *
 * Stops any current playback and plays the song associated with the button clicked.
 *
 * @param button The button that corresponds to the selected level's song.
 */
void LevelWindow::playSong(QPushButton *button)
{
    if (songPaths.find(button) == songPaths.end())
        return;
    musicPlayer->stop();
    currentSongPath = songPaths[button];
    musicPlayer->setSource(QUrl("qrc" + currentSongPath));
    musicPlayer->play();
}

/**
 * @brief Pauses or resumes playback of the current song.
 *
 * If the song is playing, it pauses. If it's paused, it resumes playing.
 */
void LevelWindow::pausePlayback()
{
    if (musicPlayer->playbackState() == QMediaPlayer::PlayingState)
        musicPlayer->pause();
    else if (musicPlayer->playbackState() == QMediaPlayer::PausedState)
        musicPlayer->play();
}

/**
 * @brief Stops the current song playback.
 *
 * This function will stop the song and reset the playback.
 */

void LevelWindow::stopPlayback()
{
    if (musicPlayer->playbackState() != QMediaPlayer::StoppedState)
        musicPlayer->stop();
}

/**
 * @brief Restarts the current song from the beginning.
 *
 * This function will stop and play the song from the start again.
 */
void LevelWindow::restartPlayback()
{
    if (!currentSongPath.isEmpty())
    {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl("qrc" + currentSongPath));
        musicPlayer->play();
    }
}
