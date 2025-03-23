#include "user.h"
#include "databasemanager.h"

User::User(QString username) {
    this->username=username;
    this->user_id=getUserId();

    this->highScore = (this->user_id != -1) ? getHighscore() : 0;
    insertHighscore(this->highScore);
}

User::User(QString username, int score) {
    this->username=username;
    this->user_id=getUserId();

    this->highScore = (this->user_id != -1) ? getHighscore() : 0;
    if (score > this->highScore) {
        this->highScore = score;
        insertHighscore(this->highScore);
    }
}

QString User::getUsername(){
    return this->username;
}

int User::getUserId(){
    DatabaseManager dm;
    dm.connectDatabase();
    QSqlQuery query;

    query.prepare("SELECT user_id FROM users WHERE username = :username");
    query.bindValue(":username", this->username);

    if (!query.exec()){
        qDebug() << "(User: getUserId) User ID query failed.";
        return -1;
    }

    if (query.next()){
        this->user_id=query.value(0).toInt();
        qDebug() << "User ID: " << this->user_id;

        return this->user_id;
    }
    return -1;
}

int User::getHighscore(){
    DatabaseManager dm;
    dm.connectDatabase();
    QSqlQuery query;

    query.prepare("SELECT highscore FROM high_scores WHERE user_id = :user_id");
    query.bindValue(":user_id", this->user_id);

    if (!query.exec()){
        qDebug() << "(User: getHighscore) User highscore query failed.";
        return 0;
    }

    if (query.next()){
        this->highScore=query.value(0).toInt();
        return this->highScore;
    }
    return 0;
}

int User::getLevelscore(int level){
    DatabaseManager dm;
    dm.connectDatabase();
    QSqlQuery query;

    query.prepare("SELECT score FROM level_scores WHERE user_id = :user_id AND level = :level");
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":level", level);

    if (!query.exec()){
        qDebug() << "(User: getLevelscore) User level score query failed.";
    }

    if (query.next()){
        int score=query.value(0).toInt();
        return score;
    }
    return -1;
}

bool User::insertHighscore(int highscore){
    QSqlQuery query;

    if (this->user_id == -1) {
        qDebug() << "(User: insertHighscore) Invalid user_id, cannot insert highscore.";
        return false;
    }

    // insert user info into high_scores and level_scores
    query.prepare("INSERT INTO high_scores(user_id, highscore) VALUES (:user_id, :highscore)"
                  "ON DUPLICATE KEY UPDATE highscore = GREATEST(highscore, :highscore)");
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":highscore", highscore);

    if (!query.exec()){
        qDebug() << "(User: insertHighscore) Error: " << query.lastError().text();
        return false;
    }

    qDebug() <<"User highscore inserted successfully!";
    return true;
}

bool User::insertLevelscore(int level, int score){
    QSqlQuery query;

    if (this->user_id == -1) {
        qDebug() << "(User: insertLevelscore) Invalid user_id, cannot insert highscore.";
        return false;
    }

    // insert user info into high_scores and level_scores
    query.prepare("INSERT INTO level_scores(user_id, level, score) VALUES (:user_id, :level, :score)"
                  "ON DUPLICATE KEY UPDATE score = GREATEST(score, :score)");
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":level", level);
    query.bindValue(":score", score);

    if (!query.exec()){
        qDebug() << "(User: insertLevelscore) Error: " << query.lastError().text();
        return false;
    }

    qDebug() <<"User highscore inserted successfully!";
    return true;
}
