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
    void setHighscore(int newScore);
private:
    QString username;
    int highScore;

    friend class UserFactory;
};

#endif // USER_H
