/**
 * @file user.h
 * @author Allison So
 * @date March 30, 2025
 * @brief File containing user header.
 *
 */
#ifndef USER_H
#define USER_H

#include <QString>
#include <map>
/**
 * @brief The User class
 *
 * The user class stores and manages user information like username, user_id, highscore, and level scores.
 */
class User
{
public:
    /**
     * @brief User
     * @param parent
     *
     * The User class is responsible for managing Users.
     */
    /**
     * @brief User
     * @param username
     * Constructor that requires a username.
     */
    User(QString username);
    /**
     * @brief getLevelscore
     * @param level
     * Returns score for given level.
     */
    int getLevelscore(int level);
    /**
     * @brief getUserId
     * Queries database for user_id.
     */
    int getUserId();
    /**
     * @brief getUsername
     * Returns user object stored username.
     */
    QString getUsername();
    /**
     * @brief getUsername
     * @param user_id
     * Queries database for username with given user_id.
     */
    QString getUsername(int user_id);
    /**
     * @brief getHighscore
     * Queries database for user highscore.
     */
    int getHighscore();
    /**
     * @brief getLevels
     * Returns mapped list of pairs (level, score).
     */
    std::map<int, int> getLevels();
    /**
     * @brief insertHighscore
     * @param highscore
     * Inserts or updates highscore in database.
     */
    bool insertHighscore(int highscore);
    /**
     * @brief insertLevelscore
     * @param level, score
     * Inserts or updates level score in database.
     */
    bool insertLevelscore(int level, int score);
private:
    int user_id;
    QString username;
    int highScore;
    std::map<int, int> levelScores;

    friend class UserFactory;
};

#endif // USER_H
