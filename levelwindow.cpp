#include "levelwindow.h"
#include <QSpacerItem>
#include <QSizePolicy>
#include <QTemporaryFile>

LevelWindow::LevelWindow(QWidget *parent) : QMainWindow(parent) {
    layout = new QVBoxLayout(this);
    setStyleSheet("background-color: #F5EFFF;");

    // Add spacer at top
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Creating title
    title = new QLabel("Select Level", this);
    title->setStyleSheet("QLabel { color: #924AEB; }");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

    // Creating level buttons
    levelButton1 = new QPushButton("Easy", this);
    layout->addWidget(levelButton1);
    levelButton1->setFixedSize(300, 50);
    levelButton1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    levelButton2 = new QPushButton("Medium", this);
    layout->addWidget(levelButton2);
    levelButton2->setFixedSize(300, 50);
    levelButton2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    levelButton3 = new QPushButton("Hard", this);
    layout->addWidget(levelButton3);
    levelButton3->setFixedSize(300, 50);
    levelButton3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Apply styles to buttons
    QString buttonStyle = "QPushButton {"
                          "background-color: #E9A5F1;"
                          "border-radius: 15px;"
                          "color: white;"
                          "border: 2px solid #DD8DF5;"
                          "padding: 10px;"
                          "font-size: 16px;"
                          "font-weight: bold;"
                          "min-width: 300px;"
                          "min-height: 50px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #C68EFD;"
                          "border: 2px solid #924AEB;"
                          "}";
    // Apply styles to each button
    levelButton1->setStyleSheet(buttonStyle);
    levelButton2->setStyleSheet(buttonStyle);
    levelButton3->setStyleSheet(buttonStyle);

    // Store the buttons and their matching songs
    QPushButton* levelButtons[] = {levelButton1, levelButton2, levelButton3};
    QString levelSongs[] = {":/audio/easysong.mp3", ":/audio/mediumsong.mp3", ":/audio/hardsong.mp3"};

    // Connect buttons to songs
    for (int i = 0; i < 3; i++){
        QPushButton* button = levelButtons[i];
        songPaths[button] = levelSongs[i];

        connect(button, &QPushButton::pressed, this, [this, button] { playPreview(button); });
        connect(button, &QPushButton::clicked, this, [this, button] { playFullSong(button); });

    }

    // Set alignment for all widgets
    layout->setAlignment(Qt::AlignCenter);
    // Add spacer at bottom
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Layout setup
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Fonts
    QFont titleFont("Helvetica", 50, QFont::Bold);
    title->setFont(titleFont);

    QFont buttonFont("Helvetica", 16, QFont::Light);
    levelButton1->setFont(buttonFont);
    levelButton2->setFont(buttonFont);
    levelButton3->setFont(buttonFont);

    // Song buttons
    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);
    restartButton= new QPushButton("Replay", this);

    // Connecting song buttons
    connect(pauseButton, &QPushButton::clicked, this, &LevelWindow::pausePlayback);
    connect(stopButton, &QPushButton::clicked, this, &LevelWindow::stopPlayback);
    connect(restartButton, &QPushButton::clicked, this, &LevelWindow::restartPlayback);
}


// void LevelWindow::playPreview(QPushButton *button){
//     if (songPaths.find(button) == songPaths.end()) return;
//     stopPlayback();

//     currentSongPath = songPaths[button];
//     if (musicPlayer.openFromFile(currentSongPath.toStdString())) {
//         musicPlayer.play();
//     } else {
//         qDebug() << "Failed to play preview: " << currentSongPath;
//     }
// }

void LevelWindow::playPreview(QPushButton *button){
    if (songPaths.find(button) == songPaths.end()) return;
    stopPlayback();

    currentSongPath = songPaths[button];
    QTemporaryFile tempFile;
    tempFile.setAutoRemove(true);
    if (tempFile.open()){
        QFile::copy(currentSongPath, tempFile.fileName());
        if (musicPlayer.openFromFile(currentSongPath.toStdString())) {
            musicPlayer.play();
            sf::Time duration = sf::seconds(20);
            musicPlayer.setPlayingOffset(duration);
            stopPlayback();
        } else {
            qDebug() << "Failed to play preview: " << currentSongPath;
        }
    }
}

// Play full song when clicked
// void LevelWindow::playFullSong(QPushButton *button){
//     if (songPaths.find(button) == songPaths.end()) return;
//     stopPlayback();

//     currentSongPath = songPaths[button];
//     if (musicPlayer.openFromFile(currentSongPath.toStdString())) {
//         musicPlayer.play();
//     } else {
//         qDebug() << "Failed to play song: " << currentSongPath;
//     }
// }

void LevelWindow::playFullSong(QPushButton *button){
    if (songPaths.find(button) == songPaths.end()) return;
    stopPlayback();

    currentSongPath = songPaths[button];

    QTemporaryFile tempFile;
    tempFile.setAutoRemove(true);
    if (tempFile.open()){
        QFile::copy(currentSongPath, tempFile.fileName());
        if (musicPlayer.openFromFile(tempFile.fileName().toStdString())) {
            musicPlayer.play();
        } else {
            qDebug() << "Failed to play song: " << currentSongPath;
        }
    }
}

// Pause the song
void LevelWindow::pausePlayback(){
    // Pause the song
    if (musicPlayer.getStatus() == sf::Music::Playing)
        musicPlayer.pause();
    // resume the song
    if (musicPlayer.getStatus() == sf::Music::Paused)
        musicPlayer.play();
}

// Stop the song
void LevelWindow::stopPlayback(){
    if (musicPlayer.getStatus() == sf::Music::Playing || musicPlayer.getStatus() == sf::Music::Paused)
        musicPlayer.stop();
}

// Restart play
void LevelWindow::restartPlayback(){
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
