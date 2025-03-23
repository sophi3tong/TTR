#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QCoreApplication>
#include <levelwindow.h>
#include <userfactory.h>

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
private slots:
    void setupUI(int isLogin);
    void handleRegister();
    void handleBackToLogin();
    void handleLogin();
    void handleCreate();
    void connectDatabase();
    void checkDrivers();
    bool insertUser(const QString& firstname, const QString& lastname, const QString& username, const QString& password);
    bool authenticateUser(const QString& username, const QString& password);
private:
    QVBoxLayout *layout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QLineEdit *firstnameInput;
    QLineEdit *lastnameInput;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *btl_button;
    QPushButton *create_button;
    QPushButton *register_button;
    QPushButton *login_button;
    QLabel *login_error;
    LevelWindow *levelScreen;
};

#endif // LOGINWINDOW_H
