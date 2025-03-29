#include "song.h"
#include "levelwindow.h"
#include <QVBoxLayout>
#include <QDir>
#include <QDebug>


Song::Song(QWidget *parent) : QMainWindow(parent)

{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);


    // Page to select BPM (Difficulty Level)
    bpmPage = new QWidget();
    QVBoxLayout *bpmLayout = new QVBoxLayout(bpmPage);

    int bpmRanges[] = {100, 111, 121, 131, 141};
    for (int bpm : bpmRanges) {
        QPushButton *btn = new QPushButton(QString::number(bpm) + "-" + QString::number(bpm + 9), this);
        connect(btn, &QPushButton::clicked, this, [this, bpm] {
            BPMSelection(bpm);
        });
        bpmLayout->addWidget(btn);
    }

    stackedWidget->addWidget(bpmPage);

    // Select a Song
    songPage = new QWidget();
    QVBoxLayout *songLayout = new QVBoxLayout(songPage);
    songList = new QListWidget(this);

    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);
    restartButton= new QPushButton("Replay", this);

    songLayout->addWidget(songList);
    songLayout->addWidget(pauseButton);
    songLayout->addWidget(stopButton);
    songLayout->addWidget(restartButton);

    stackedWidget->addWidget(songPage);

    connect(songList, &QListWidget::itemEntered, this, &Song::playPreview);
    connect(songList, &QListWidget::itemClicked, this, &Song::playFullSong);
    connect(pauseButton, &QPushButton::clicked, this, &Song::pausePlayback);
    connect(stopButton, &QPushButton::clicked, this, &Song::stopPlayback);
    connect(restartButton, &QPushButton::clicked, this, &Song::restartPlayback);
}

// Deconstructor method
Song::~Song(){}

void Song::playPreview(QListWidgetItem *item){
    if (!item || songPaths.find(item) == songPaths.end()) return;

    stopPlayback();
    currentSongPath = songPaths[item];

    if (musicPlayer.openFromFile(currentSongPath.toStdString())) {
        musicPlayer.play();
    } else {
        qDebug() << "Failed to play preview: " << currentSongPath;
    }
}

// Play full song when clicked
void Song::playFullSong(QListWidgetItem *item){
    if (!item || songPaths.find(item) == songPaths.end()) return;

    // Stop the preview and the play the song in full
    if (musicPlayer.getStatus() == sf::Music::Playing)
        musicPlayer.stop();

    if (musicPlayer.openFromFile(songPaths[item].toStdString())) {
        musicPlayer.play();
    } else {
        qDebug() << "Failed to play song: " << songPaths[item];
    }
}

// Pause the song
void Song::pausePlayback(){
    // Pause the song
    if (musicPlayer.getStatus() == sf::Music::Playing)
        musicPlayer.pause();
    // resume the song
    if (musicPlayer.getStatus() == sf::Music::Paused)
        musicPlayer.play();
}

// Stop the song
void Song::stopPlayback(){
    if (musicPlayer.getStatus() == sf::Music::Playing || musicPlayer.getStatus() == sf::Music::Paused)
        musicPlayer.stop();
}

// Restart playc
void Song::restartPlayback(){
    if (musicPlayer.getStatus() == sf::Music::Playing || musicPlayer.getStatus() == sf::Music::Paused) {
        stopPlayback();

        // Restart the same song if one was playing
        if (!currentSongPath.isEmpty()) {
            if (musicPlayer.openFromFile(currentSongPath.toStdString())) {
                musicPlayer.play();
            } else {
                qDebug() << "Failed to restart song: " << currentSongPath;
            }
        }
    }
}
