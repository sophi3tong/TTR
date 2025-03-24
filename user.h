#ifndef USER_H
#define USER_H

#include <QString>
#include <map>

class User
{
public:
    User(QString username);
    User(QString username, int score);
    QString getUsername();
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
    int getLevelscore(int level);
    int getUserId();

    friend class UserFactory;
};

#endif // USER_H
