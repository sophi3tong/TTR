/**

* @file mainwindow.cpp
* @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
* @date March 30, 2025

* @brief File containing main window functions.

*

*/

#include "mainwindow.h"
#include "levelwindow.h"
#include "loginwindow.h"
#include "tutorial.h"  // Include the Tutorial header
#include <QSpacerItem>
#include <QSizePolicy>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
/**
 * @brief MainWindow::MainWindow
 * @param parent
 *
 * This is the main window.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    layout = new QVBoxLayout(this);
    setStyleSheet("QMainWindow { background-color: #F5EFFF; }");
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));
    title = new QLabel("Main Menu", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("QLabel { color: #924AEB; }");
    layout->addWidget(title);
    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

    // buttons
    playButton = new QPushButton("Play", this);
    layout->addWidget(playButton);
    playButton->setFixedSize(300, 50);
    playButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tutorialButton = new QPushButton("Tutorial", this);  // Create the Tutorial button before logout
    layout->addWidget(tutorialButton);
    tutorialButton->setFixedSize(300, 50);
    tutorialButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    logoutButton = new QPushButton("Logout", this);
    layout->addWidget(logoutButton);
    logoutButton->setFixedSize(300, 50);
    logoutButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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

    playButton->setStyleSheet(buttonStyle);
    logoutButton->setStyleSheet(buttonStyle);
    tutorialButton->setStyleSheet(buttonStyle);  // Apply the style to the tutorial button

    // alignment
    layout->setAlignment(Qt::AlignCenter);

    // Add spacer at bottom
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // layout setup
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // fonts
    QFont titleFont("Helvetica", 50, QFont::Bold);
    title->setFont(titleFont);
    QFont buttonFont("Helvetica", 16, QFont::Light);
    playButton->setFont(buttonFont);
    logoutButton->setFont(buttonFont);
    tutorialButton->setFont(buttonFont);  // Set the font for the tutorial button
    connect(playButton, &QPushButton::clicked, this, [this]() {

        QString username = this->username;
        UserFactory uf;
        User loginUser = uf.createUser(username);
        qDebug() << "(Main Window Check) Username:" << loginUser.getUsername();

        // Hide the Main Menu window
        this->hide();
        // Show the LevelWindow
        LevelWindow *levelWindow = new LevelWindow(this);
        levelWindow->username = this->username;
        connect(levelWindow, &QObject::destroyed, this, &MainWindow::show);
        levelWindow->showMaximized();

    });

    connect(logoutButton, &QPushButton::clicked, this, [this]() {

        // Hide the Main Menu window
        this->hide();

        // Show the LoginWindow
        LoginWindow *loginWindow = new LoginWindow(this);
        connect(loginWindow, &QObject::destroyed, this, &MainWindow::show);
        loginWindow->showMaximized();

    });

    // Connect the Tutorial button to the openTutorialWindow slot
    connect(tutorialButton, &QPushButton::clicked, this, &MainWindow::openTutorialWindow);

}

MainWindow::~MainWindow() {}

/**
 * @brief MainWindow::openLevelWindow
 *
 * This opens the level window.
 */
void MainWindow::openLevelWindow() {

    // Create an instance of LevelWindow
    LevelWindow *levelWindow = new LevelWindow();

    // Show the LevelWindow maximized
    levelWindow->showMaximized();

    // Optionally, hide the MainWindow (if you want to hide the main menu after opening the level window)
    this->hide();

}
/**
 * @brief MainWindow::openTutorialWindow
 *
 * This opens the tutorial window.
 */
void MainWindow::openTutorialWindow() {

    if (!tutorialWindow) {  // Create it only if it doesn't already exist
        tutorialWindow = new Tutorial(this);
        connect(tutorialWindow, &QObject::destroyed, [this]() { tutorialWindow = nullptr; });

    }

    tutorialWindow->showMaximized();
    this->hide();

}

