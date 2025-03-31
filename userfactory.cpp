/**
 * @file userfactory.cpp
 * @author Allison So
 * @date March 30, 2025
 * @brief File containing user factory functions.
 *
 */
#include "userfactory.h"
/**
 * @brief UserFactory::UserFactory
 *
 * Basic constructor.
 */
UserFactory::UserFactory() {}
/**
 * @brief UserFactory::createUser
 * @param username
 * Creates a User object given a username.
 */
User UserFactory::createUser(QString username){
    return User(username);
}

