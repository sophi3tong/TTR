#include "scoremanager.h"

ScoreManager::ScoreManager(User newUser) {
    this->currentScore=0;
    this->user=newUser;
    this->highScore=newUser.getHighscore();
    this->levelScore=newUser.getLevels();
    this->comboCounter=0;
    this->multiplier=0;
}

int ScoreManager::getCurrentscore(){
    return this->currentScore;
}

void ScoreManager::updateCurrentscore(int newScore){
    this->currentScore=newScore;
}

void ScoreManager::resetCurrentscore(){
    this->currentScore=0;
}

int ScoreManager::getHighscore(){
    return this->highScore;
}

void ScoreManager::updateHighscore(int newScore){
    this->highScore=newScore;
}

void ScoreManager::saveHighscore() {
    this->user.setHighscore(this->highScore);
}

int ScoreManager::getLevelscore(int level){
    auto it = this->levelScore.find(level);

    if (it!=this->levelScore.end()){
        return it->second;
    }
    return 0;
}

int ScoreManager::getCombocounter(){
    return this->comboCounter;
}

void ScoreManager::increaseCombocounter(){
    this->comboCounter++;
}

void ScoreManager::resetCombocounter(){
    this->comboCounter=0;
}

int ScoreManager::getMultiplier() {
    return this->multiplier;
}
void ScoreManager::increaseMultiplier(){
    this->multiplier++;
}

void ScoreManager::resetMultiplier(){
    this->multiplier=0;
}
