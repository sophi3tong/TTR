#include "levelwindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>
#include "loginwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;  // Initialize LoginWindow

    w.showMaximized();
    return a.exec();
}
