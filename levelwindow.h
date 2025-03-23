#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>
#include <SFML/Audio.hpp>
#include <QListWidget>

class LevelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelWindow(QWidget *parent = nullptr);
    void playPreview(QPushButton *item);
    void playFullSong(QPushButton *item);
    void pausePlayback();
    void stopPlayback();
    void restartPlayback();

private:
    QVBoxLayout *layout;
    QLabel *title;
    QPushButton *levelButton1;
    QPushButton *levelButton2;
    QPushButton *levelButton3;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *restartButton;
    QMap<QPushButton*, QString> songPaths;
    QListWidget *songList;
    QString currentSongPath;
    sf::Music musicPlayer;
};

#endif // LEVELWINDOW_H

#include <QMainWindow>

