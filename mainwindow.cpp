#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    layout = new QVBoxLayout(this);

    // Add spacer at top
    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Creating title
    title = new QLabel("Main Menu", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

    // Creating buttons
    playButton = new QPushButton("Play", this);
    layout->addWidget(playButton);
    playButton->setFixedSize(300, 50);
    playButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    logoutButton = new QPushButton("Logout", this);
    layout->addWidget(logoutButton);
    logoutButton->setFixedSize(300, 50);
    logoutButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
    playButton->setFont(buttonFont);
    logoutButton->setFont(buttonFont);
}

MainWindow::~MainWindow() {}
