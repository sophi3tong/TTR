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
