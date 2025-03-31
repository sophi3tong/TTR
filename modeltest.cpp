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

bool ModelTest::testUserFactory(){
    try {
        UserFactory uf;
        qDebug() << "UserFactory creation test: Success";
        return true;
    } catch(...){
        qDebug() << "UserFactory creation test: Failed";
        return false;
    }
}

bool ModelTest::testUserFactoryCreate(){
    try{
        UserFactory uf;
        User user = uf.createUser("TestUser");

        if (user.getUsername().isEmpty()) {
            qDebug() << "UserFactory create User test: Failed";
            return false;
        }
        qDebug() << "UserFactory create User test: Success";
        return true;
    } catch (...) {
        qDebug() << "UserFactory create User test: Failed";
        return false;
    }
}

bool ModelTest::testUser(){
    try{
        User user = User("TestUser2");

        if (user.getUsername().isEmpty()) {
            qDebug() << "User creation test: Failed";
            return false;
        }
        qDebug() << "User creation test: Success";
        return true;
    } catch (...) {
        qDebug() << "User creation test: Failed";
        return false;
    }
}

bool ModelTest::testUserGetUserID(){
    try{
        User user = User("TestUser2");

        if (user.getUserId()==-1) {
            qDebug() << "User getUserID test: Failed";
            return false;
        }
        qDebug() << "User getUserID test: Success";
        return true;
    } catch (...) {
        qDebug() << "User getUserID test: Failed";
        return false;
    }
}

bool ModelTest::testUserGetHighscore(){
    try{
        User user = User("TestUser2");

        if (user.getHighscore()==-1) {
            qDebug() << "User getHighscore test: Failed";
            return false;
        }
        qDebug() << "User getHighscore test: Success";
        return true;
    } catch (...) {
        qDebug() << "User getHighscore test: Failed";
        return false;
    }
}

bool ModelTest::testUserInsertHighscore(){
    try{
        User user = User("TestUser2");

        if (user.insertHighscore(20)) {
            qDebug() << "User getHighscore test: Success";
            return true;
        }
        qDebug() << "User getHighscore test: Failed";
        return false;
    } catch (...) {
        qDebug() << "User getHighscore test: Failed";
        return false;
    }
}

#include "modeltest.moc"
