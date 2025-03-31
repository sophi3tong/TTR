/**
 * @file loginwindow.h
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date March 30, 2025
 * @brief File containing login window header.
 *
 */
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <levelwindow.h>
#include <userfactory.h>

#include <databasemanager.h>
/**
 * @brief The LoginWindow class
 *
 * The login window displays the login window for users to login.
 */
class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief LoginWindow
     * @param parent
     *
     * The LoginWindow class is responsible for displaying the login interface where users can log in or register.
     * It also handles the interactions with the user authentication system.
     */
    explicit LoginWindow(QWidget *parent = nullptr);
    /**
     * @brief username
     *
     * Stores the username.
     */
    QString username;

private slots:
    /**
     * @brief setupUI
     * @param isLogin
     *
     * This method sets up the user interface.
     */
    void setupUI(int isLogin);
    /**
     * @brief handleRegister
     *
     * This is triggered when the user clicks the Register button.
     */
    void handleRegister();
    /**
     * @brief handleBackToLogin
     *
     * This is triggered when the user clicks the Back to Login button.
     */
    void handleBackToLogin();
    /**
     * @brief handleLogin
     *
     * This is triggered when the user clicks the Login button and thier user account already exists.
     */
    void handleLogin();
    /**
     * @brief handleCreate
     *
     * This is triggered when the user clicks the Create button when making a new user.
     */
    void handleCreate();
    /**
     * @brief insertUser
     * @param firstname
     * @param lastname
     * @param username
     * @param password
     * @return
     *
     * This inserts a new user with the provided informaiton in the database.
     */
    bool insertUser(const QString& firstname, const QString& lastname, const QString& username, const QString& password);
    /**
     * @brief authenticateUser
     * @param username
     * @param password
     * @return
     *
     * This method checks the database for a matching username and password.
     */
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
