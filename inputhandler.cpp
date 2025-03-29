#include "inputhandler.h"
#include "levelwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>
#include <QPalette>
#include <QTimer>
#include <QInputDialog>
#include <QApplication>

InputHandler::InputHandler(QWidget *parent)
    : QWidget(parent)
{
    initializeUI();

    roundTimer = new QTimer(this);
    connect(roundTimer, &QTimer::timeout, this, [this]()
            {
        --timeLeft;
        timerLabel->setText("Time Left: " + QString::number(timeLeft));

        if (timeLeft <= 0) {
            roundTimer->stop();
            if (!targetLetters.empty()) {
                showWarning("Time's up!");
                handleMistake();
                generateRandomLetters();
                updateLabel();
                updateStatus();
            }
        } });

    connect(restartButton, &QPushButton::clicked, this, &InputHandler::restartGame);
    connect(backButton, &QPushButton::clicked, this, [this]()
            {
        this->close();
        LevelWindow *menu = new LevelWindow();
        menu->show(); });

    loadHighScore();
}

void InputHandler::initializeUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    this->setStyleSheet("background-color: #F5EFFF;");

    QLabel *title = new QLabel("Typing Challenge", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont("Helvetica", 36, QFont::Bold);
    title->setFont(titleFont);
    title->setStyleSheet("color: #924AEB;");
    mainLayout->addWidget(title);
    mainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

    label = new QLabel("Press keys to match letters!", this);
    label->setAlignment(Qt::AlignCenter);
    QFont labelFont("Helvetica", 24);
    label->setFont(labelFont);
    mainLayout->addWidget(label);

    timerLabel = new QLabel(this);
    timerLabel->setAlignment(Qt::AlignCenter);
    QFont infoFont("Helvetica", 18);
    timerLabel->setFont(infoFont);
    timerLabel->setStyleSheet("color: #555;");
    mainLayout->addWidget(timerLabel);

    statusLabel = new QLabel(this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setFont(infoFont);
    statusLabel->setStyleSheet("color: #555;");
    mainLayout->addWidget(statusLabel);

    warningLabel = new QLabel("", this);
    warningLabel->setAlignment(Qt::AlignCenter);
    QFont warningFont("Helvetica", 18, QFont::Bold);
    warningLabel->setFont(warningFont);
    warningLabel->setStyleSheet("color: red; padding-top: 10px;");
    mainLayout->addWidget(warningLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    restartButton = new QPushButton("Restart Game", this);
    backButton = new QPushButton("Back to Menu", this);

    QFont buttonFont("Helvetica", 16, QFont::Bold);
    QString buttonStyle = "QPushButton {"
                          "background-color: #E9A5F1;"
                          "border-radius: 15px;"
                          "color: white;"
                          "border: 2px solid #DD8DF5;"
                          "padding: 10px;"
                          "min-width: 150px;"
                          "min-height: 40px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #C68EFD;"
                          "border: 2px solid #924AEB;"
                          "}";

    restartButton->setFont(buttonFont);
    backButton->setFont(buttonFont);
    restartButton->setStyleSheet(buttonStyle);
    backButton->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(restartButton);
    buttonLayout->addWidget(backButton);
    mainLayout->addLayout(buttonLayout);

    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    setLayout(mainLayout);
    setWindowTitle("Letter Matching Game");
    resize(600, 400);
}

void InputHandler::showWarning(const QString &message)
{
    warningLabel->setText(message);
    QTimer::singleShot(1500, this, [this]()
                       { warningLabel->clear(); });
}

void InputHandler::launchEasyMode()
{
    difficultyRange = qMakePair(1, 2);
    isHardMode = true;
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::launchMediumMode()
{
    difficultyRange = qMakePair(3, 5);
    isHardMode = true;
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::launchHardMode()
{
    difficultyRange = qMakePair(6, 8);
    isHardMode = true;
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::generateRandomLetters()
{
    targetLetters.clear();
    int numLetters = QRandomGenerator::global()->bounded(difficultyRange.first, difficultyRange.second + 1);
    for (int i = 0; i < numLetters; ++i)
    {
        QChar ch = QChar('A' + QRandomGenerator::global()->bounded(26));
        targetLetters.push_back(ch);
    }

    if (isHardMode)
    {
        timeLeft = 5;
        timerLabel->setText("Time Left: " + QString::number(timeLeft));
        roundTimer->start(1000);
    }
    else
    {
        timerLabel->clear();
        roundTimer->stop();
    }
}

void InputHandler::processInput(QChar userInput)
{
    if (gameOver)
        return;

    userInput = userInput.toUpper();

    if (!targetLetters.empty() && userInput == targetLetters[0])
    {
        targetLetters.erase(targetLetters.begin());

        if (targetLetters.empty())
        {
            ++score;
            roundTimer->stop();
            generateRandomLetters();
        }
    }
    else
    {
        handleMistake();
    }

    updateLabel();
    updateStatus();
}

void InputHandler::updateLabel()
{
    QString displayText;
    for (QChar ch : targetLetters)
    {
        displayText += ch;
        displayText += ' ';
    }
    label->setText(displayText.trimmed());
}

void InputHandler::updateStatus()
{
    if (gameOver)
    {
        statusLabel->setText("Game Over! Score: " + QString::number(score) + " | High Score: " + QString::number(highScore));
        return;
    }

    statusLabel->setText("Score: " + QString::number(score) + " | Lives: " + QString::number(lives) + " | High Score: " + QString::number(highScore));
}

void InputHandler::handleMistake()
{
    --lives;

    label->setText("Wrong!");
    QPalette pal = label->palette();
    pal.setColor(QPalette::WindowText, Qt::red);
    label->setPalette(pal);

    QTimer::singleShot(600, this, [this]()
                       {
        QPalette pal = label->palette();
        pal.setColor(QPalette::WindowText, Qt::black);
        label->setPalette(pal);
        updateLabel(); });

    if (lives <= 0)
    {
        gameOver = true;
        roundTimer->stop();
        if (score > highScore)
        {
            highScore = score;
            saveHighScore();
        }
    }
}

void InputHandler::restartGame()
{
    score = 0;
    lives = 3;
    gameOver = false;
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::loadHighScore()
{
    QFile file("highscore.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in >> highScore;
    }
    file.close();
}

void InputHandler::saveHighScore()
{
    QFile file("highscore.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << highScore;
    }
    file.close();
}

void InputHandler::keyPressEvent(QKeyEvent *event)
{
    QChar key = event->text().at(0);
    if (key.isLetter())
    {
        processInput(key);
    }
}
