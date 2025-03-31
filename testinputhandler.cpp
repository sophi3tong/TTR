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
    void testTimer();
    void testInput();
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
    inputhandler->show(); // test display
    inputhandler->hide();
    inputhandler->stopMusic();
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
    inputhandler->hide();
    inputhandler->stopMusic();
}

/**
 * @test
 * @brief test that keyboard inputs are being read correctly
*/
void TestInputHandler::testInput(){
    qDebug() << "Testing User Input functionalities";
    // Generate random letters for testing
    InputHandler ih("TestUser");
    ih.generateRandomLetters();

    // when user uses correct input
    // Check that the targetLetters are not empty
    if (!ih.getTargetLetters().isEmpty()){
        // get correct input
        QChar correctInput = ih.getTargetLetters().first();
        // count number of target letters
        int origTargetLetters = ih.getTargetLetters().count();
        // get initial score
        int initialScore = ih.getScore();

        // test processInput() function
        ih.processInput(correctInput);
        int currTargetLetters = ih.getTargetLetters().count();
        QVERIFY2(ih.getScore() == initialScore + 1, "Test Failed: score updated incorrectly");
        QVERIFY2(origTargetLetters == currTargetLetters + 1, "Test Failed: Letter not removed from list correctly");
    }

    // when user uses incorrect input
    int currLives = ih.getLives();
    // Simulate incorrect key press
    ih.processInput('X');
    QVERIFY2(ih.getLives() == currLives - 1, "Test Failed: Lives not updated correctly");
    ih.hide();
    inputhandler->stopMusic();
}

#include "testinputhandler.moc"
