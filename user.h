#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString username);
    User(QString username, int score);
    QString getUsername();
    int getHighscore();
    int getLevelscore(int level);
    void setHighscore(int score);
    void setLevelscore(int level, int score);
private:
    int user_id;
    QString username;
    int highScore;
    bool insertHighscore(QString username, int highscore);
    int getUserId();
    bool insertHighscore(int highscore);
    bool insertLevelscore(int level, int score);

    friend class UserFactory;
};

#endif // USER_H
