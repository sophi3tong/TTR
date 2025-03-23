#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <vector>

class InputHandler : public QWidget
{
    Q_OBJECT

public:
    InputHandler(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void generateRandomLetters();
    void processInput(QChar userInput);
    void updateLabel();
    void updateStatus();
    void handleMistake();
    void restartGame();
    void loadHighScore();
    void saveHighScore();

    QLabel *label;
    QLabel *statusLabel;
    QPushButton *restartButton;

    std::vector<QChar> targetLetters;
    int score = 0;
    int lives = 3;
    int highScore = 0;
    bool gameOver = false;
};

#endif // INPUTHANDLER_H
