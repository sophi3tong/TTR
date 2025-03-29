#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QChar>
#include <QKeyEvent>
#include <QTimer>
#include <QPair>

class InputHandler : public QWidget
{
    Q_OBJECT

public:
    InputHandler(QWidget *parent = nullptr);
    void launchEasyMode();
    void launchMediumMode();
    void launchHardMode();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    // UI Elements
    QLabel *label;
    QLabel *statusLabel;
    QLabel *timerLabel;
    QPushButton *restartButton;
    QPushButton *backButton;
    QLabel *warningLabel;

    // Game State
    QVector<QChar> targetLetters;
    int score = 0;
    int lives = 3;
    int highScore = 0;
    bool gameOver = false;

    // Difficulty Settings
    QPair<int, int> difficultyRange;
    bool isHardMode = false;

    // Timer for Hard Mode
    QTimer *roundTimer;
    int timeLeft = 5;

    // Methods
    void generateRandomLetters();
    void processInput(QChar userInput);
    void updateLabel();
    void updateStatus();
    void handleMistake();
    void restartGame();
    void loadHighScore();
    void saveHighScore();
    void initializeUI();
    void showWarning();
    void showWarning(const QString &message);
};

#endif // INPUTHANDLER_H
