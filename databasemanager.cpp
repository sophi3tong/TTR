/**
/**
 * @file databasemanager.h
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date March 30, 2025
 * @brief File containig database manager functions.
 *
 * This file contains the implementation of the DatabaseManager class, which is
 * responsible for managing the connection to the MySQL database and checking
 * the availability of drivers.
 *
 */
#include "databasemanager.h"


/**
 * @brief Default constructor for DatabaseManager
 *
 * Initializes a new instance of the DatabaseManager class.
 *
 */

DatabaseManager::DatabaseManager() {}
/**
 * @brief Displays the available database drivers.
 *
 * This function prints out the list of available database drivers to the debug
 * console, which helps in checking if the necessary drivers are present.
 */
void DatabaseManager::checkDrivers() {
    qDebug() << "Available drivers: " << QSqlDatabase::drivers();
}

/**
 * @brief Connects to the MySQL database
 *
 * This function establishes a connection to the MySQL database using the
 * provided connection details (hostname, port, database name, username, and
 * password). It checks for available drivers and attempts to open the
 * database connection. If successful, a success message is printed. Otherwise,
 * an error message is logged.
 *
 */
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
