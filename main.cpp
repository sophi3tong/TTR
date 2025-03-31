/**
 * @file main.cpp
 * @author Julie Vo
 * @date March 30, 2025
 * @brief File containing level window functions.
 *
 */
#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>
#include "loginwindow.h"
#include "modeltest.cpp"
#include "soundadjtest.cpp"
#include "testdatabasemanager.cpp"
#include "testinputhandler.cpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Tests
    ModelTest test;
    QTest::qExec(&test, argc, argv);

    soundAdjTest soundtest;
    QTest::qExec(&soundtest, argc, argv);

    TestDatabaseManager dbtest;
    QTest::qExec(&dbtest, argc, argv);

    TestInputHandler inputtest;
    QTest::qExec(&inputtest, argc, argv);

    LoginWindow w;  // Initialize LoginWindow

    w.showMaximized();
    return a.exec();
}
