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
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>

class InputHandler : public QWidget
{
    Q_OBJECT

public:
    explicit InputHandler(QWidget *parent = nullptr);
    void launchEasyMode();
    void launchMediumMode();
    void launchHardMode();

signals:
    void backToMenu();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    // UI Elements
    QLabel *label;
    QLabel *statusLabel;
    QLabel *livesLabel;
    QLabel *timerLabel;
    QLabel *warningLabel;
    QLabel *scoreLabel;
    QPushButton *restartButton;
    QPushButton *backButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;

    // Game State
    QVector<QChar> targetLetters;
    int score = 0;
    int lives = 3;
    int highScore = 0;
    bool gameOver = false;
    bool isPaused = false;

    // Difficulty Settings
    QPair<int, int> difficultyRange;
    bool isHardMode = false;

    // Timer for Hard Mode
    QTimer *roundTimer;
    int timeLeft = 5;

    // Music
    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;
    QHBoxLayout *topRightLayout;
    QSlider *volumeSlider;
    QPushButton *volumeButton;
    bool isVisible;
    QWidget *topRightWidget;


    // Methods
    void generateRandomLetters();
    void processInput(QChar userInput);
    void updateLabel();
    void updateStatus();
    void handleMistake();
    void restartGame();
    void pauseGame();
    void resumeGame();
    void loadHighScore();
    void saveHighScore();
    void initializeUI();
    void stopMusic();
    void showWarning(const QString &message);
};

#endif // INPUTHANDLER_H
