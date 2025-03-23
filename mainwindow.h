#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout *layout;
    QLabel *title;
    QPushButton *playButton;
    QPushButton *logoutButton;
};

#endif // MAINWINDOW_H
