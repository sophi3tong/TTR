#include "inputhandler.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>
#include <QPalette>
#include <QTimer>

InputHandler::InputHandler(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    label = new QLabel("Press keys to match letters!", this);
    statusLabel = new QLabel(this);
    restartButton = new QPushButton("Restart Game", this);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(statusLabel);
    bottomLayout->addWidget(restartButton);

    mainLayout->addWidget(label);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    setWindowTitle("Letter Matching Game");
    resize(400, 200);

    connect(restartButton, &QPushButton::clicked, this, &InputHandler::restartGame);

    loadHighScore();
    generateRandomLetters();
    updateLabel();
    updateStatus();
}

void InputHandler::generateRandomLetters()
{
    targetLetters.clear();
    int numLetters = QRandomGenerator::global()->bounded(1, 6); // [1,5]
    for (int i = 0; i < numLetters; ++i)
    {
        QChar ch = QChar('A' + QRandomGenerator::global()->bounded(26));
        targetLetters.push_back(ch);
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

    QTimer::singleShot(600, this, [this]() {
        QPalette pal = label->palette();
        pal.setColor(QPalette::WindowText, Qt::black);
        label->setPalette(pal);
        updateLabel();
    });

    if (lives <= 0)
    {
        gameOver = true;
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
    QChar key = event->text().at(0);
    if (key.isLetter())
    {
        processInput(key);
    }
}
