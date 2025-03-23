#include "userfactory.h"

UserFactory::UserFactory() {}

User UserFactory::createUser(QString username){
    return User(username);
}

User UserFactory::createUser(QString username, int score){
    return User(username, score);
}
