/**
 * @file levelwindow.cpp
 * @author Julie Vo
 * @date March 30, 2025
 * @brief File containing level window functions.
 *
 */
#include "userfactory.h"

UserFactory::UserFactory() {}

User UserFactory::createUser(QString username){
    return User(username);
}

