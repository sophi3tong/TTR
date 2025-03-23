#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <map>
#include <user.h>

class ScoreManager
{
public:
    ScoreManager(User newUser);

    int getCurrentscore();
    void updateCurrentscore(int newScore);
    void resetCurrentscore();

    int getHighscore();
    void updateHighscore(int newScore);

    int getLevelscore(int score);
    void saveHighscore();

    int getCombocounter();
    void increaseCombocounter();
    void resetCombocounter();

    int getMultiplier();
    void increaseMultiplier();
    void resetMultiplier();
private:
    int currentScore;
    int highScore;
    std::map<int, int> levelScore;
    int comboCounter;
    int multiplier;
    User user;
};

#endif // SCOREMANAGER_H
