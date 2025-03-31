#include "modeltest.h"

bool ModelTest::testUserFactory(){
    UserFactory uf;
    if (!uf) {
        qDebug() << "UserFactory creation test: Failed";
        return false;
    }
    qDebug() << "UserFactory creation test: Success";
    return true;
}

bool ModelTest::testUser(){

}
