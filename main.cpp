#include "levelwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w;
    w.showMaximized();
    return a.exec();
}
