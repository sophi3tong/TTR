/**
 * @file levelwindow.cpp
 * @author Julie Vo
 * @date March 30, 2025
 * @brief File containing level window functions.
 *
 */
#include "databasemanager.h"

DatabaseManager::DatabaseManager() {}

void DatabaseManager::checkDrivers() {
    qDebug() << "Available drivers: " << QSqlDatabase::drivers();
}

void DatabaseManager::connectDatabase(){
    QCoreApplication::addLibraryPath("/usr/local/share/qt/plugins");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("ttr-database.cnm8mega2y8r.us-east-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("ttr_db");
    db.setUserName("admin");
    db.setPassword("ttr-database123");

    checkDrivers();

    if (!db.open()) {
        qDebug() << "Error: Could not open database!" << db.lastError().text();
        return;
    }
    qDebug() << "Database connected successfully!";
}
