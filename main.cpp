#include "mainwindow.h"
#include "levelwindow.h"
#include <QApplication>
#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}


// #include "levelwindow.h"
// #include <QApplication>
// #include <QMediaPlayer>
// #include <QAudioOutput>
// #include <QUrl>
// #include <QDebug>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     LevelWindow w;

//     // // Create the media player and audio output
//     // QMediaPlayer *music = new QMediaPlayer();
//     // QAudioOutput *audioOutput = new QAudioOutput();

//     // // Connect the media player to the audio output
//     // music->setAudioOutput(audioOutput);

//     // // Set the media source (the audio file path)
//     // QUrl mediaUrl("qrc:/audio/easysong.mp3");
//     // music->setSource(mediaUrl);

//     // // Set the volume (optional)
//     // audioOutput->setVolume(50);

//     // music->play();


//     w.showMaximized();
//     return a.exec();
// }
