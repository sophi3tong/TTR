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
#include <QDebug>
#include "tutorial.h"  // Include TutorialWindow header

/**
 * @brief The MainWindow class
 *
 * This is the main window class.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent
     *
     * This makes the main window.
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief username
     *
     * This is a space for the username to be saved.
     */
    QString username;
private slots:
    /**
     * @brief openLevelWindow
     *
     * This opens the level window.
     */
    void openLevelWindow();  // Declare the openLevelWindow slot
    void openTutorialWindow();
private:

    QVBoxLayout *layout;
    QLabel *title;
    QPushButton *playButton;
    QPushButton *logoutButton;
    QPushButton *tutorialButton;  // Tutorial Button
    Tutorial *tutorialWindow;

};

#endif // MAINWINDOW_H
