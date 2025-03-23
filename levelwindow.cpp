#include "levelwindow.h"
#include <QSpacerItem>
#include <QSizePolicy>

LevelWindow::LevelWindow(QWidget *parent) : QMainWindow(parent) {
    layout = new QVBoxLayout(this);
    setStyleSheet("background-color: #F5EFFF;");

    // Add spacer at top
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Creating title
    title = new QLabel("Select Level", this);
    title->setStyleSheet("QLabel { color: #924AEB; }");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

    // Creating level buttons
    levelButton1 = new QPushButton("Easy", this);
    layout->addWidget(levelButton1);
    levelButton1->setFixedSize(300, 50);
    levelButton1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    levelButton2 = new QPushButton("Medium", this);
    layout->addWidget(levelButton2);
    levelButton2->setFixedSize(300, 50);
    levelButton2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    levelButton3 = new QPushButton("Hard", this);
    layout->addWidget(levelButton3);
    levelButton3->setFixedSize(300, 50);
    levelButton3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Apply styles to buttons
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
    // Apply styles to each button
    levelButton1->setStyleSheet(buttonStyle);
    levelButton2->setStyleSheet(buttonStyle);
    levelButton3->setStyleSheet(buttonStyle);

    // Set alignment for all widgets
    layout->setAlignment(Qt::AlignCenter);
    // Add spacer at bottom
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Layout setup
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Fonts
    QFont titleFont("Helvetica", 50, QFont::Bold);
    title->setFont(titleFont);

    QFont buttonFont("Helvetica", 16, QFont::Light);
    levelButton1->setFont(buttonFont);
    levelButton2->setFont(buttonFont);
    levelButton3->setFont(buttonFont);


}
