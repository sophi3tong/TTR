/**
 * @file mainwindow.h
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date March 30, 2025
 * @brief File containing main window header.
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "levelwindow.h"  // Include LevelWindow header
#include <QDebug>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString username;
private slots:
    void openLevelWindow();  // Declare the openLevelWindow slot

private:

    QVBoxLayout *layout;
    QLabel *title;
    QPushButton *playButton;
    QPushButton *logoutButton;
};

#endif // MAINWINDOW_H
