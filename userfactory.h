/**
 * @file userfactory.h
 * @author Allison So
 * @date March 30, 2025
 * @brief File containing user factory header.
 *
 */
#ifndef USERFACTORY_H
#define USERFACTORY_H

#include <QString>
#include <user.h>
/**
 * @brief The UserFactory class
 *
 * The user factory creates users.
 */
class UserFactory
{
public:
    /**
     * @brief UserFactory
     * @param parent
     *
     * The UserFactory class is responsible for creating Users.
     */
    /**
     * @brief UserFactory
     *
     * Basic constructor.
     */
    UserFactory();
    /**
     * @brief createUser
     * @param username
     * Creates a User object given a username.
     */
    User createUser(QString username);
};

#endif // USERFACTORY_H
