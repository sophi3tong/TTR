/**
 * @file testdatabasemanager.cpp
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date 30 March 2025
 * @brief Testing the databasemanager.cpp file
 *
 */

#include <QtTest/QTest>
#include <databasemanager.h>
#include <iostream>

class TestDatabaseManager : public QObject{
    Q_OBJECT

private slots:
    void test_checkDrivers();
    void test_connectDatabase();

};

/** @test
 * @brief checking if all necessary drivers are present
 *
 */
void TestDatabaseManager::test_checkDrivers(){
    std::cout << "Testing: checkDrivers()";
    DatabaseManager dbManager;
    // Call the checkDrivers() method to start test
    dbManager.checkDrivers();

    QStringList driverList = QSqlDatabase::drivers();
    // Verify that the driverList is not empty 
    QVERIFY2(!driverList.isEmpty(), "Test Failed: driver list is empty");
    // Verify that QMYSQL is in driverList
    QVERIFY2(driverList.contains("QMYSQL"), "Test Failed: driver list does not contain QMYSQL");
}

/** @test
 * @brief checking if the database is being connected properly
 *
 */
void TestDatabaseManager::test_connectDatabase(){
    std::cout << "Testing: connectDatabase()";
    DatabaseManager dbManager;
    // Call the connectDatabase() method to start test
    dbManager.connectDatabase();

    // If the database is open then it was connected properly
    QSqlDatabase sqldb = QSqlDatabase::database();
    if (sqldb.isOpen()) {
        qDebug() << "Test Passed";
    }
    else{
        qDebug() << "Test Failed: " << sqldb.lastError().text(); // Print error specific to database connection failure
    }
}

#include "testdatabasemanager.moc"
