#ifndef MODELTEST_H
#define MODELTEST_H

#include <QtTest/QtTest>
#include <user.h>
#include <userfactory.h>

class ModelTest : public QObject{
    Q_OBJECT
private slots:
    bool testUserFactory();
    bool testUserFactoryCreate();
    bool testUser();
    bool testUserGetUserID();
    bool testUserGetHighscore();
    bool testUserInsertHighscore();
};
#endif // MODELTEST_H
