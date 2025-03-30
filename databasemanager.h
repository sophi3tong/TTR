/**
 * @file levelwindow.cpp
 * @author Julie Vo
 * @date March 30, 2025
 * @brief File containing level window functions.
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

class DatabaseManager
{
public:
    DatabaseManager();
    void connectDatabase();
    void checkDrivers();
};

#endif // DATABASEMANAGER_H
