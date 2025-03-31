/**
 * @file userfactory.h
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date March 30, 2025
 * @brief File containing user factory header.
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
};

#endif // USERFACTORY_H
