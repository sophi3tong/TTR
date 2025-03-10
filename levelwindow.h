#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>

class LevelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelWindow(QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QLabel *title;
    QPushButton *levelButton1;
    QPushButton *levelButton2;
    QPushButton *levelButton3;
};

#endif // LEVELWINDOW_H

#include <QMainWindow>

