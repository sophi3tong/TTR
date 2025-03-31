/**
 * @file testinputhandler.cpp
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date 30 March 2025
 * @brief testing the inputhandler.cpp functionalities
 *
*/

#include "userfactory.h"
#include <inputhandler.h>
#include <QtTest/QTest>
#include <iostream>

class TestInputHandler : public QObject{
    Q_OBJECT

private slots:
    void initTestCase();
    void testUI();
    void testTimer();
    void testPauseandResume();
    void testInput();
    void cleanUpTestCase();
private:
    InputHandler *inputhandler;
};

/**
 * @brief initialize an input handler for the test case
*/
void TestInputHandler::initTestCase(){
    // Test case: (TestUser)
    UserFactory uf;
    User testUser = User("TestUser");
    inputhandler = new InputHandler(testUser.getUsername());
    inputhandler->show(); // display inputhandler to be used for testing
}

/**
 * @test
 * @brief testing all UI components
*/
void TestInputHandler::testUI(){
    qDebug() << "Testing UI Components";
    // test that all labels are not null
    // if null, print fail message
    QVERIFY2(inputhandler->findChild<QLabel *>("label") != nullptr, "Test Failed: label not found");
    QVERIFY2(inputhandler->findChild<QLabel *>("statusLabel") != nullptr, "Test Failed: statusLabel not found");
    QVERIFY2(inputhandler->findChild<QLabel *>("livesLabel") != nullptr, "Test Failed: livesLabel not found");
    QVERIFY2(inputhandler->findChild<QLabel *>("timerLabel") != nullptr, "Test Failed: timerLabel not found");
    QVERIFY2(inputhandler->findChild<QLabel *>("warningLabel") != nullptr, "Test Failed: warningLabel not found");
    QVERIFY2(inputhandler->findChild<QLabel *>("scoreLabel") != nullptr, "Test Failed: scoreLabel not found");
    QVERIFY2(inputhandler->findChild<QLabel *>("highscoreLabel") != nullptr, "Test Failed: highscoreLabel not found");

    // test that all buttons are not null
    // if null, print fail message
    QVERIFY2(inputhandler->findChild<QPushButton *>("restartButton") != nullptr, "Test Failed: restartButton not found");
    QVERIFY2(inputhandler->findChild<QPushButton *>("pauseButton") != nullptr, "Test Failed: pauseButton not found");
    QVERIFY2(inputhandler->findChild<QPushButton *>("resumeButton") != nullptr, "Test Failed: resumeButton not found");
    QVERIFY2(inputhandler->findChild<QPushButton *>("backButton") != nullptr, "Test Failed: backButton not found");
}

/**
 * @test
 * @brief initialize an input handler for the test case
*/
void TestInputHandler::testTimer(){
    std::cout << "Testing: Timer functionalities";
    // Launch game mode for testing 
    inputhandler->launchEasyMode();
    // Save the initial allotted time to a variable
    int allottedTime = inputhandler->timeLeft;

    // wait for timer to countdown
    QTest::qWait(3000);
    QVERIFY2(inputhandler->timeLeft == allottedTime - 3, "Test Failed: Timer malfunction");
}

/**
 * @test
 * @brief testing functionalities of pause and resume buttons
*/
void TestInputHandler::testPauseandResume(){
    qDebug() << "Testing the Pause and Resume Buttons";
    InputHandler ih("TestUser");
    // Test the pause button
    QTest::mouseClick(ih.pauseButton, Qt::LeftButton);
    QVERIFY2(inputhandler->isPaused == true, "Test Failed: Pause button not working");
    // Test the restart button
    QTest::mouseClick(ih.resumeButton, Qt::LeftButton);
    QVERIFY2(inputhandler->isPaused == false, "Test Failed: Resume button not working");
}

/**
 * @test
 * @brief test that keyboard inputs are being read correctly
*/
void TestInputHandler::testInput(){
    qDebug() << "Testing User Input functionalities";
    // Generate random letters for testing
    inputhandler->generateRandomLetters();

    // when user uses correct input
    // Check that the targetLetters are not empty
    if (!inputhandler->getTargetLetters().isEmpty()){
        // get correct input
        QChar correctInput = inputhandler->getTargetLetters().first();
        // get initial score
        int initialScore = inputhandler->getScore();

        // test processInput() function
        inputhandler->processInput(correctInput);
        QVERIFY2(inputhandler->getScore() == initialScore + 1, "Test Failed: score updated incorrectly");
        QVERIFY2(inputhandler->getTargetLetters().isEmpty(), "Test Failed: Letter not removed from list correctly");
    }

    // when user uses incorrect input
    int currLives = inputhandler->getLives();
    // Simulate incorrect key press
    inputhandler->processInput('X');
    QVERIFY2(inputhandler->getLives() == currLives - 1, "Test Failed: Lives not updated correctly");
}

/**
 * @brief delete inputhandler after testing is complete
*/
void TestInputHandler::cleanUpTestCase(){
    delete inputhandler;
}

#include "testinputhandler.moc"
