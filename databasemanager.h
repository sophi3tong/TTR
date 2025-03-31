/**
 * @file databasemanager.h
 * @author Allison So
 * @date March 30, 2025
 * @brief File containig database manager header.
 *
 * This file contains the declaration of the DatabaseManager class, which manages
 * the connection to the MySQL database used in the game.
 *
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QCoreApplication>

/**
 * @brief A database manager that represents the database used in the game
 *
 * This database manager class manages the database in the game and contains all the user's informatino
 *
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 */
class DatabaseManager
{
public:
    /**
     * @brief Constructs a new DatabaseManager object.
     */
    DatabaseManager();
    /**
     * @brief Connects to the MySQL database.
     *
     * Establishes a connection to the MySQL database using predefined
     * credentials and connection details (hostname, port, database name,
     * username, and password).
     */
    void connectDatabase();

    /**
     * @brief Prints the available SQL drivers.
     *
     * Displays the list of available database drivers to the debug console.
     * This function is useful for ensuring that the necessary drivers for
     * the database connection are available.
     */
    void checkDrivers();
};

#endif // DATABASEMANAGER_H
