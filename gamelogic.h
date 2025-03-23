#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <song.h>
#include <QString>
#include <scoremanager.h>
#include <inputhandler.h>

class GameLogic
{
public:
    GameLogic();
    void startGame();
    void pauseGame();
    void updateGame(float score);
    void endGame();
    void loadSong(Song newSong);
private:
    QString currentSong;
    ScoreManager sm;
    InputHandler ih;
    bool isRunning;
    int currentLevel;
};

#endif // GAMELOGIC_H
