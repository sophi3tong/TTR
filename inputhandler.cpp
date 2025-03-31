/**
 * @file inputhandler.h
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date March 30, 2025
 * @brief File containing input handler functions.
 *
 * This file contains the implementation of the inputhandler class. It consist of the actually typing game and
 * how the game deals with the input by the user (ie. if user incorrectly/correctly types letter, music playing, pause, resume, etc.)
 *
 */
#include "inputhandler.h"
#include "user.h"
#include "userfactory.h"
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
#include <QSlider>
#include <QWidget>

/**
     * @brief InputHandler
     * @param username
     * @param parent
     *
     * Initializes the InputHandler class, sets up the UI components,
     * and loads the current player's high score.
     */
InputHandler::InputHandler(QString username, QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "(InputHandler top) Username:" << username;
    this->username = username;
    loadHighScore();
    initializeUI();
    this->setFixedSize(800, 500);

    roundTimer = new QTimer(this);
    connect(roundTimer, &QTimer::timeout, this, [this]() {
        if (gameOver || isPaused) return;

        --timeLeft;
        timerLabel->setText("Time Left: " + QString::number(timeLeft));

        if (timeLeft <= 0) {
            roundTimer->stop();

            if (!targetLetters.isEmpty()) {
                showWarning("Time's up!");
                handleMistake();          // lose a life
                updateLabel();
                updateStatus();

                // Move to next random letters after a short pause
                QTimer::singleShot(800, this, [this]() {
                    if (!gameOver) {
                        generateRandomLetters();
                        updateLabel();
                    }
                });
            }
        }
    });

    connect(restartButton, &QPushButton::clicked, this, &InputHandler::restartGame);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        stopMusic();  // Stop the music in InputHandler
        emit backToMenu();  // Emit signal to go back to the menu
        this->close();  // Close the current InputHandler window
    });

    connect(pauseButton, &QPushButton::clicked, this, &InputHandler::pauseGame);
    connect(resumeButton, &QPushButton::clicked, this, &InputHandler::resumeGame);

    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    connect(musicPlayer, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            musicPlayer->setPosition(0);
            musicPlayer->play();
        }
    });
}

void InputHandler::initializeUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setStyleSheet("background-color: #F5EFFF;");

    // Adjust volume button with icon
    volumeButton = new QPushButton(this);
    volumeButton->setIcon(QIcon(":/icons/volume-up.png"));
    volumeButton->setIconSize(QSize(20, 20));
    volumeButton->setStyleSheet("QPushButton { background: transparent; border: none; }");
    volumeButton->setFixedSize(40, 40);

    // Add a horizontal layout for the volume slider
    QHBoxLayout *topRightLayout = new QHBoxLayout;
    topRightLayout->addStretch();  // Pushes the slider to the right
    topRightLayout->addWidget(volumeButton);

    // Create the volume slider (hidden by default)
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);  // Range is from 0 (mute) to 100 (max volume)
    volumeSlider->setValue(50);      // Set initial volume to 50%
    volumeSlider->setVisible(false); // Initially hide the slider
    topRightLayout->addWidget(volumeSlider);

    QWidget *topRightWidget = new QWidget(this);
    topRightWidget->setLayout(topRightLayout);
    // Add the top right layout to the main layout
    mainLayout->addWidget(topRightWidget,0, Qt::AlignTop | Qt::AlignRight);

    // Connect volume button to toggle visibility of slider
    connect(volumeButton, &QPushButton::clicked, this, [this]() {
        bool isVisible = volumeSlider->isVisible();
        volumeSlider->setVisible(!isVisible);
        // Change button icon based on visibility
        if (isVisible) {
            volumeButton->setIcon(QIcon(":/icons/volume-up.png")); // Show volume icon when slider is hidden
            volumeButton->setIconSize(QSize(20, 20));
        } else {
            volumeButton->setIcon(QIcon(":/icons/cancel.png"));   // Show close (X) icon when slider is visible
            volumeButton->setIconSize(QSize(20, 20));
        }
    });

    // Connect the slider's value change to control audio volume
    connect(volumeSlider, &QSlider::valueChanged, this, [this](int value) {
        audioOutput->setVolume(value / 100.0);  // QAudioOutput volume is set from 0 to 1
    });

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

    livesLabel = new QLabel("Lives: 3", this);  // Added lives label
    livesLabel->setAlignment(Qt::AlignLeft);
    QFont livesFont("Helvetica", 16);
    livesLabel->setFont(livesFont);
    livesLabel->setStyleSheet("color: #333;");
    mainLayout->addWidget(livesLabel);

    highscoreLabel = new QLabel("Highscore: "+QString::number(this->highScore), this);
    highscoreLabel->setAlignment(Qt::AlignLeft);
    QFont highscoreFont("Helvetica", 16);
    highscoreLabel->setFont(highscoreFont);
    highscoreLabel->setStyleSheet("color: #333;");
    mainLayout->addWidget(highscoreLabel);

    label = new QLabel("Press keys to match letters!", this);
    label->setAlignment(Qt::AlignCenter);
    QFont labelFont("Helvetica", 24);
    label->setFont(labelFont);
    label->setStyleSheet("color: #924AEB;");
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
    QHBoxLayout *button2Layout = new QHBoxLayout;
    restartButton = new QPushButton("Restart Game", this);
    backButton = new QPushButton("Back to Menu", this);
    pauseButton = new QPushButton("Pause", this);
    resumeButton = new QPushButton("Resume", this);

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
    pauseButton->setFont(buttonFont);
    resumeButton->setFont(buttonFont);

    restartButton->setStyleSheet(buttonStyle);
    backButton->setStyleSheet(buttonStyle);
    pauseButton->setStyleSheet(buttonStyle);
    resumeButton->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(restartButton);
    buttonLayout->addWidget(backButton);
    button2Layout->addWidget(pauseButton);
    button2Layout->addWidget(resumeButton);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(button2Layout);

    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(mainLayout);
    setWindowTitle("Type Type Revolution");
    resize(600, 400);
}

void InputHandler::showWarning(const QString &message)
{
    warningLabel->setText(message);
    QTimer::singleShot(1500, this, [this]() {
        warningLabel->clear();
    });
}

/**
     * @brief InputHandler::launchEasyMode()
     *
     * Lauches the game in Easy mode.
     */
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

/**
     * @brief InputHandler::launchMediumMode()
     *
     * Lauches the game in Medium mode.
     */
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
/**
 * @brief InputHandler::launchHardMode
 *
 * Lauches the game in Medium mode.
 */
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

/**
 * @brief InputHandler::generateRandomLetters
 *
 * This generates random letters for the game.
 */
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

/**
 * @brief InputHandler::processInput
 * @param userInput
 *
 * This processes the input of the user when typing.
 */
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

/**
 * @brief InputHandler::updateLabel
 *
 * This updates the label by removing the letter on screen when user types it correctly.
 */
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

/**
 * @brief InputHandler::updateStatus
 *
 * This updates the status of the game.
 */
void InputHandler::updateStatus()
{
    scoreLabel->setText("Score: " + QString::number(score));
    livesLabel->setText("Lives: " + QString::number(lives));  // Update lives label
}

/**
 * @brief InputHandler::handleMistake
 * This handles a mistake that the user does when inputting the wrong letter.
 */
void InputHandler::handleMistake()
{
    --lives;

    // Flash the current letter string in red
    QString originalStyle = label->styleSheet();
    label->setStyleSheet("color: red;");

    if (lives <= 0)
    {
        saveHighScore();
        highscoreLabel->setText("Highscore: " + QString::number(this->highScore));
        gameOver = true;
        roundTimer->stop();
        musicPlayer->stop();

        // Clear target letters so no more input is expected
        targetLetters.clear();

        // Show "Game Over!" on the letter display label
        label->setStyleSheet("color: #924AEB;");
        label->setText("Game Over!");

        // Show guidance message in the warning label
        warningLabel->setText("Game Over! Press Restart or Back to Menu");

        return; // Prevent further label updates
    }

    // If not game over, revert flash and refresh label
    QTimer::singleShot(150, this, [this, originalStyle]() {
        label->setStyleSheet(originalStyle);
    });

    QTimer::singleShot(600, this, [this]() {
        updateLabel();
    });
}

/**
 * @brief InputHandler::restartGame
 *
 * This restarts the game.
 */
void InputHandler::restartGame()
{
    score = 0;
    lives = 3;
    gameOver = false;
    isPaused = false;

    label->setStyleSheet("color: #924AEB;");
    warningLabel->clear();
    generateRandomLetters();
    updateLabel();
    updateStatus();

    if (musicPlayer) {
        musicPlayer->setPosition(0);
        musicPlayer->play();
    }
}

/**
 * @brief InputHandler::loadHighScore
 *
 * This loads the high score of current user.
 *
 */
void InputHandler::loadHighScore()
{
    QString username = this->username;
    UserFactory uf;
    User loginUser = uf.createUser(username);
    qDebug() << "(InputHandler::loadHighScore) Username:" << username;
    this->highScore = loginUser.getHighscore();
}

/**
 * @brief InputHandler::saveHighScore
 *
 * This saves the high score of current user.
 */
void InputHandler::saveHighScore()
{
    QString username = this->username;
    UserFactory uf;
    User loginUser = uf.createUser(username);
    qDebug() << "(InputHandler::saveHighScore) Username:" << loginUser.getUsername();
    loginUser.insertHighscore(score);
}

/**
 * @brief InputHandler::keyPressEvent
 * @param event
 *
 * Processes the user's input and check if the entered letter matches the target letter.
 * Updates the game state based on user input.
 */
void InputHandler::keyPressEvent(QKeyEvent *event)
{
    if (isPaused || gameOver) return;

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

/**
 * @brief InputHandler::pauseGame
 *
 * This pauses the game.
 */
void InputHandler::pauseGame()
{
    isPaused = true;

    if (roundTimer && roundTimer->isActive()) {
        roundTimer->stop();
    }
    if (musicPlayer) {
        musicPlayer->pause();
    }

    label->setText("Game Paused!\nPress Resume to continue");
}


/**
 * @brief InputHandler::resumeGame
 *
 * This resumes the game.
 */
void InputHandler::resumeGame()
{
    isPaused = false;

    if (!gameOver && timeLeft > 0) {
        if (roundTimer) {
            roundTimer->start();
        }
        if (musicPlayer) {
            musicPlayer->play();
        }
    }

    updateLabel();
}

/**
 * @brief InputHandler::stopMusic
 *
 * This stops the music
 */
void InputHandler::stopMusic()
{
    if (musicPlayer) {
        musicPlayer->stop();
    }
}

