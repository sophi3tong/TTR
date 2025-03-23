#include "user.h"

User::User(QString username) {
    this->username=username;
    this->highScore=0;
}

User::User(QString username, int score) {
    this->username=username;
    this->highScore=score;
}

QString User::getUsername(){
    return this->username;
}

int User::getHighscore(){
    return this->highScore;
}

void User::setHighscore(int newScore){
    this->highScore=newScore;
    return;
}
