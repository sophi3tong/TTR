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
