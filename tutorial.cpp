/**
 * @file tutorial.cpp
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date 30 March 2025
 * @brief This is the tutorial window to teach users how to play the game.
 *
*/
#include "tutorial.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>

/**
 * @brief Tutorial::Tutorial
 * @param mainWindow
 * @param parent
 *
 * This makes the tutorial window visible to user
 */
Tutorial::Tutorial(MainWindow *mainWindow, QWidget *parent)

    : QWidget(parent), mainWindow(mainWindow) {

    qDebug() << "Tutorial Window Created";

    // Set up main layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create QLabel for displaying the image
    tutorialImage = new QLabel(this);

    QPixmap pixmap(":/icons/tutorial.png");

    if (pixmap.isNull()) {

        qDebug() << "Failed to load tutorial.png!";

    }

    tutorialImage->setPixmap(pixmap);
    tutorialImage->setAlignment(Qt::AlignCenter);

    // Add QLabel to layout
    layout->addWidget(tutorialImage);

    // Create a spacer to push the button to the bottom
    layout->addStretch(1);

    // Create Back to Menu button (ONLY this button)
    QPushButton *backButton = new QPushButton("Back to Menu", this);
    backButton->setFixedSize(200, 40);
    layout->addWidget(backButton);
    layout->setAlignment(backButton, Qt::AlignCenter);  // Center the button

    // Apply the same button style as in MainWindow
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

    backButton->setStyleSheet(buttonStyle);

    // Connect "Back to Menu" button
    connect(backButton, &QPushButton::clicked, this, [this, mainWindow]() {
        if (mainWindow) {
            mainWindow->show();  // Show MainWindow
        }

        this->hide();  // Hide Tutorial window

    });

    setLayout(layout);

}

/**
 *
 * @brief Tutorial::~Tutorial
 *
 * This checks if tutorial window is destroyed
 */
Tutorial::~Tutorial() {

    qDebug() << "Tutorial Window Destroyed";


}


