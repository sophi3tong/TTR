#include "levelwindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>
#include "loginwindow.h"


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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;  // Initialize LoginWindow

    w.showMaximized();
    return a.exec();
}
