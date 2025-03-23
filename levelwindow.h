#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

class LevelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelWindow(QWidget *parent = nullptr);
    void playSong(QPushButton *item);  // Play song when button is clicked

private:
    QVBoxLayout *layout;
    QLabel *title;
    QPushButton *levelButton1;
    QPushButton *levelButton2;
    QPushButton *levelButton3;
    QMap<QPushButton*, QString> songPaths;
    QString currentSongPath;

    // Media player and audio output for playback
    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;
};

#endif // LEVELWINDOW_H
