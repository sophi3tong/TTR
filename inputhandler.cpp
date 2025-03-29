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
#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

InputHandler::InputHandler(QWidget *parent)
    : QWidget(parent)
{
    initializeUI();

    roundTimer = new QTimer(this);
    connect(roundTimer, &QTimer::timeout, this, [this]() {
        if (gameOver) return;

        --timeLeft;
        timerLabel->setText("Time Left: " + QString::number(timeLeft));

        if (timeLeft <= 0) {
            roundTimer->stop();
            if (!targetLetters.isEmpty()) {
                showWarning("Time's up!");
                handleMistake();
                updateLabel();
                updateStatus();
            }
        }
    });

    connect(restartButton, &QPushButton::clicked, this, &InputHandler::restartGame);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToMenu();
        this->close();
    });

    loadHighScore();

    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
}

void InputHandler::initializeUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setStyleSheet("background-color: #F5EFFF;");

    QLabel *title = new QLabel("Typing Challenge", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont("Helvetica", 36, QFont::Bold);
    title->setFont(titleFont);
    title->setStyleSheet("color: #924AEB;");
    mainLayout->addWidget(title);
    mainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setAlignment(Qt::AlignLeft);
    QFont scoreFont("Helvetica", 16);
    scoreLabel->setFont(scoreFont);
    scoreLabel->setStyleSheet("color: #333;");
    mainLayout->addWidget(scoreLabel);

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
    QTimer::singleShot(1500, this, [this]() {
        warningLabel->clear();
    });
}

void InputHandler::launchEasyMode()
{
    difficultyRange = qMakePair(1, 2);
    isHardMode = true;
    gameOver = false;
    score = 0;
    lives = 3;
    musicPlayer->setSource(QUrl("qrc:/audio/easysong.mp3"));
    musicPlayer->play();
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::launchMediumMode()
{
    difficultyRange = qMakePair(3, 5);
    isHardMode = true;
    gameOver = false;
    score = 0;
    lives = 3;
    musicPlayer->setSource(QUrl("qrc:/audio/mediumsong.mp3"));
    musicPlayer->play();
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::launchHardMode()
{
    difficultyRange = qMakePair(6, 8);
    isHardMode = true;
    gameOver = false;
    score = 0;
    lives = 3;
    musicPlayer->setSource(QUrl("qrc:/audio/hardsong.mp3"));
    musicPlayer->play();
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::generateRandomLetters()
{
    if (gameOver) return;
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
    if (gameOver) return;

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
    scoreLabel->setText("Score: " + QString::number(score));
}

void InputHandler::handleMistake()
{
    --lives;

    label->setText("Wrong!");
    QPalette pal = label->palette();
    pal.setColor(QPalette::WindowText, Qt::red);
    label->setPalette(pal);

    QTimer::singleShot(600, this, [this]() {
        QPalette pal = label->palette();
        pal.setColor(QPalette::WindowText, Qt::black);
        label->setPalette(pal);
        updateLabel();
    });

    if (lives <= 0)
    {
        gameOver = true;
        roundTimer->stop();
        musicPlayer->stop();
        label->setText("Game Over!");
        warningLabel->setText("Press Restart or Back to Menu");
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
    warningLabel->clear();
    if (musicPlayer) musicPlayer->play();
}

void InputHandler::loadHighScore()
{
    QFile file("highscore.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> highScore;
    }
    file.close();
}

void InputHandler::saveHighScore()
{
    QFile file("highscore.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << highScore;
    }
    file.close();
}

void InputHandler::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) return;
    if (event->key() == Qt::Key_Backspace) return;

    QString text = event->text();
    if (text.isEmpty()) return;

    QChar key = text.at(0);
    if (key.isLetter())
    {
        processInput(key);
    }
}
