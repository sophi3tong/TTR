/**
 * @file user.h
 * @author Julie Vo
 * @date March 30, 2025
 * @brief File containing user header.
 *
 */
#ifndef USER_H
#define USER_H

#include <QString>
#include <map>

class User
{
public:
    User(QString username);
    User(QString username, int score);
    User getUser(int user_id);
    int getLevelscore(int level);
    int getUserId();
    QString getUsername();
    QString getUsername(int user_id);
    int getHighscore();
    std::map<int, int> getLevels();
    void setHighscore(int score);
    void setLevelscore(int level, int score);
    bool insertHighscore(int highscore);
    bool insertLevelscore(int level, int score);
private:
    int user_id;
    QString username;
    int highScore;
    std::map<int, int> levelScores;

    friend class UserFactory;
};

#endif // USER_H
