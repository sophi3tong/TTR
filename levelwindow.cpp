#include "levelwindow.h"
#include <QSpacerItem>
#include <QSizePolicy>
#include <QTemporaryFile>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

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

    // Initialize player and audio output
    musicPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();

    // Set audio output for the media player
    musicPlayer->setAudioOutput(audioOutput);

    // Store the buttons and their corresponding songs
    QPushButton* levelButtons[] = {levelButton1, levelButton2, levelButton3};
    QString levelSongs[] = {":/audio/easysong.mp3", ":/audio/mediumsong.mp3", ":/audio/hardsong.mp3"};

    // Connect buttons to play the corresponding songs
    for (int i = 0; i < 3; i++) {
        QPushButton* button = levelButtons[i];
        songPaths[button] = levelSongs[i]; // Map button to song

        connect(button, &QPushButton::clicked, this, [this, button] { playSong(button); });
    }

    // Optional: Set the volume
    audioOutput->setVolume(50);

}

void LevelWindow::playSong(QPushButton *button) {
    // Check if the button has a song path associated
    if (songPaths.find(button) == songPaths.end()) return;

    // Stop any currently playing song
    musicPlayer->stop();

    // Get the path of the selected song
    QString currentSongPath = songPaths[button];

    // Set the media source (song file) for the media player
    musicPlayer->setSource(QUrl("qrc" + currentSongPath));

    // Play the selected song
    musicPlayer->play();
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



// // Play full song when clicked
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

// // Pause the song
// void LevelWindow::pausePlayback() {
//     // Check if music is playing and pause it
//     if (musicPlayer.getStatus() == sf::Music::Playing) {
//         musicPlayer.pause();
//     }
//     // If it's paused, play it again
//     else if (musicPlayer.getStatus() == sf::Music::Stopped || musicPlayer.getStatus() == sf::Music::Paused) {
//         musicPlayer.play();
//     }
// }


// // Stop the song
// void LevelWindow::stopPlayback(){
//     if (musicPlayer.getStatus() == sf::Music::Playing || musicPlayer.getStatus() == sf::Music::Paused)
//         musicPlayer.stop();
// }

// // Restart play
// void LevelWindow::restartPlayback(){
//     if (musicPlayer.getStatus() == sf::Music::Playing || musicPlayer.getStatus() == sf::Music::Paused) {
//         stopPlayback();

//         // Restart the same song if one was playing
//         if (!currentSongPath.isEmpty()) {
//             if (musicPlayer.openFromFile(currentSongPath.toStdString())) {
//                 musicPlayer.play();
//             } else {
//                 qDebug() << "Failed to restart song: " << currentSongPath;
//             }
//         }
//     }
// }
