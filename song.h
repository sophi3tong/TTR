#ifndef SONG_H
#define SONG_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <SFML/Audio.hpp>
#include <unordered_map>

class Song : public QMainWindow
{
    Q_OBJECT

public:
    Song(QWidget *parent = nullptr);
    ~Song();

private slots:
    void BPMSelection(int bpm);
    void playPreview(QListWidgetItem *item);
    void playFullSong(QListWidgetItem *item);
    void pausePlayback();
    void stopPlayback();
    void restartPlayback();

private:
    QStackedWidget *stackedWidget;
    QWidget *bpmPage;
    QWidget *songPage;
    QListWidget *songList;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *restartButton;
    QString currentSongPath;

    sf::Music musicPlayer;
    std::unordered_map<QListWidgetItem*, QString> songPaths;
};
#endif // MAINWINDOW_H
