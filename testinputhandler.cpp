/**
 * @file testinputhandler.cpp
 * @author Samantha Chang
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
    void cleanUpTestCase();
private:
    InputHandler *inputhandler;
};

/**
 * @brief initialize an input handler for the test case
*/
void TestInputHandler::initTestCase(){
    // Test case: (Sophia)
    UserFactory uf;
    User testUser = User("sophia123");
    inputhandler = new InputHandler(testUser.getUsername());
    inputhandler->show(); // display inputhandler to be used for testing
}

/**
 * @test
 * @brief initialize an input handler for the test case
*/
void TestInputHandler::testTimer(){
    std::cout << "Testing: Timer functionalities";
    inputhandler->launchEasyMode();
}

/**
 * @brief delete inputhandler after testing is complete
*/
void TestInputHandler::cleanUpTestCase(){
    delete inputhandler;
}

// register tests
QTEST_MAIN(TestInputHandler);
#include 'testinputhandler.moc';
