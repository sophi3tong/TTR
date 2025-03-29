#include "levelwindow.h"
#include "inputhandler.h"
#include <QSpacerItem>
#include <QSizePolicy>
#include <QTemporaryFile>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QMainWindow>

LevelWindow::LevelWindow(QWidget *parent) : QMainWindow(parent)
{
    layout = new QVBoxLayout(this);
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
            stopPlayback();

            QString level = button->text();
            gameWindow = new InputHandler();
            connect(gameWindow, &InputHandler::backToMenu, this, []() {
                LevelWindow *newMenu = new LevelWindow();
                newMenu->show();
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

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    QFont titleFont("Helvetica", 50, QFont::Bold);
    title->setFont(titleFont);

    QFont buttonFont("Helvetica", 16, QFont::Light);
    levelButton1->setFont(buttonFont);
    levelButton2->setFont(buttonFont);
    levelButton3->setFont(buttonFont);

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

    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);
    restartButton = new QPushButton("Replay", this);

    connect(pauseButton, &QPushButton::clicked, this, &LevelWindow::pausePlayback);
    connect(stopButton, &QPushButton::clicked, this, &LevelWindow::stopPlayback);
    connect(restartButton, &QPushButton::clicked, this, &LevelWindow::restartPlayback);

    // Initialize Qt music player
    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
}

void LevelWindow::playSong(QPushButton *button)
{
    if (songPaths.find(button) == songPaths.end())
        return;
    musicPlayer->stop();
    currentSongPath = songPaths[button];
    musicPlayer->setSource(QUrl("qrc" + currentSongPath));
    musicPlayer->play();
}

void LevelWindow::pausePlayback()
{
    if (musicPlayer->playbackState() == QMediaPlayer::PlayingState)
        musicPlayer->pause();
    else if (musicPlayer->playbackState() == QMediaPlayer::PausedState)
        musicPlayer->play();
}

void LevelWindow::stopPlayback()
{
    if (musicPlayer->playbackState() != QMediaPlayer::StoppedState)
        musicPlayer->stop();
}

void LevelWindow::restartPlayback()
{
    if (!currentSongPath.isEmpty())
    {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl("qrc" + currentSongPath));
        musicPlayer->play();
    }
}
