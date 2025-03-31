/**
 * @file inputhandler.h
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date March 30, 2025
 * @brief File containing input handler header.
 *
 */
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
#include <databasemanager.h>


/**
 * @brief The InputHandler class manages the user input and game logic.
 *
 * The InputHandler class is responsible for handling the user’s keyboard inputs,
 * managing the game state (score, lives, difficulty), updating the UI,
 * and managing the background music during the game. It provides three
 * difficulty levels (Easy, Medium, Hard) and incorporates functionality
 * to pause, resume, and restart the game.
 */
class InputHandler : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief InputHandler
     * @param username
     * @param parent
     *
     * Initializes the InputHandler class, sets up the UI components,
     * and loads the current player's high score.
     */
    explicit InputHandler(QString username, QWidget *parent = nullptr);

    /**
     * @brief launchEasyMode
     *
     * Lauches the game in Easy mode.
     */
    void launchEasyMode();

    /**
     * @brief launchMediumMode
     *
     * Lauches the game in Medium mode.
     */
    void launchMediumMode();

    /**
     * @brief launchHardMode
     * Lauches the game in Hard mode.
     */
    void launchHardMode();

    /**
     * @brief username
     *
     * Current player's username.
     */
    QString username;

signals:
    /**
     * @brief backToMenu
     *
     * This signal is emitted when the player chooses to go back to the main menu.
     */
    void backToMenu();

protected:
    /**
     * @brief keyPressEvent
     * @param event
     *
     * Processes the user's input and check if the entered letter matches the target letter.
     * Updates the game state based on user input.
     */
    void keyPressEvent(QKeyEvent *event) override;

private:

    // UI Elements
    QLabel *label;
    QLabel *statusLabel;
    QLabel *livesLabel;
    QLabel *timerLabel;
    QLabel *warningLabel;
    QLabel *scoreLabel;
    QLabel *highscoreLabel;
    QPushButton *restartButton;
    QPushButton *backButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;

    // Game State
    QVector<QChar> targetLetters;
    int score = 0;
    int lives = 3;
    int highScore;
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
    /**
     * @brief generateRandomLetters
     *
     * This generates random letters for the game.
     */
    void generateRandomLetters();
    /**
     * @brief processInput
     * @param userInput
     *
     * This processes the input of the user when typing.
     */
    void processInput(QChar userInput);
    /**
     * @brief updateLabel
     *
     * This updates the label by removing the letter on screen when user types it correctly.
     */
    void updateLabel();
    /**
     * @brief updateStatus
     *
     * This updates the status of the game.
     */
    void updateStatus();
    /**
     * @brief handleMistake
     *
     * This handles a mistake that the user does when inputting the wrong letter.
     */
    void handleMistake();
    /**
     * @brief restartGame
     *
     * This restarts the game.
     */
    void restartGame();
    /**
     * @brief pauseGame
     *
     * This pauses the game.
     */
    void pauseGame();
    /**
     * @brief resumeGame
     *
     * This resumes the game.
     */
    void resumeGame();
    /**
     * @brief loadHighScore
     *
     * This loads high score.
     */
    void loadHighScore();
    /**
     * @brief saveHighScore
     *
     * This saves high score of current user.
     */
    void saveHighScore();
    /**
     * @brief initializeUI
     *
     * This displays the ui for typing window game.
     */
    void initializeUI();
    /**
     * @brief stopMusic
     *
     * This stops the music when user preses pause.
     */
    void stopMusic();
    /**
     * @brief showWarning
     * @param message
     *
     * This shows warning to the user such as a time's up warning.
     */
    void showWarning(const QString &message);
};

#endif // INPUTHANDLER_H
