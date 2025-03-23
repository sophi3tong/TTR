#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <map>
class ScoreManager
{
public:
    ScoreManager();

    int getCurrentscore();
    void updateCurrentscore();
    void resetCurrentscore();

    int getHighscore();
    void updateHighscore(int newScore);

    int getLevelscore(int score);
    void saveScore();
    void loadScore();
    void resetScore();
private:
    int currentScore;
    int highScore;
    std::map<int, int> levelScore;
    int comboCounter;
    int multiplier;
};

#endif // SCOREMANAGER_H
