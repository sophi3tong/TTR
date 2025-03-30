/**
 * @file testinputhandler.cpp
 * @author Samantha Chang
 * @date 30 March 2025
 * @brief testing the inputhandler.cpp functionalities
 *
*/

#include <inputhandler.h>
#include <QtTest/QTest>

class TestInputHandler : public QObject{
    Q_OBJECT

private slots:
    void initTestCase();
    void testTimer();
    void cleanUpTestCase();
private:
    InputHandler *inputhandler;
}

/**
 * @brief initialize an input handler for the test case
*/
void TestInputHandler::initTestCase(){
    inputhandler = new InputHandler();
    inputhandler->show(); // display inputhandler to be used for testing
}

/**
 * @test
 * @brief initialize an input handler for the test case
*/
void TestInputHandler::testTimer(){
    cout << "Testing: Timer functionalities";
    inputhandler->launchEasyMode();

    int 
}

/**
 * @brief delete inputhandler after testing is complete
*/
void TestInputHandler::cleanUpTestCase(){
    delete inputhandler;
}

// register tests
QTEST_MAIN(TestInputHandler)
#include 'testinputhandler.moc'