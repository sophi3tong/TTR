/**
 * @file levelwindow.cpp
 * @author Julie Vo
 * @date March 30, 2025
 * @brief File containing level window functions.
 *
 */
#ifndef USERFACTORY_H
#define USERFACTORY_H

#include <QString>
#include <user.h>

class UserFactory
{
public:
    UserFactory();
    User createUser(QString username);
    User createUser(QString username, int score);
};

#endif // USERFACTORY_H
