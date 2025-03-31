/**
 * @file loginwindow.cpp
 * @author Samantha Chang, Fiona Luo, Allison So, Sophia Tong, Julie Vo
 * @date March 30, 2025
 * @brief File containing login window functions.
 *
 */
#include "loginwindow.h"
#include <databasemanager.h>
#include "mainwindow.h"

/**
 * @brief LoginWindow::LoginWindow
 * @param parent
 *
 * This constructor initializes the login window by calling the `setupUI()` method.
 * It sets up the user interface for the login window.
 * By default, it sets up the window in login mode (indicated by 0).
 */
LoginWindow::LoginWindow(QWidget *parent):QMainWindow{parent}{
    setupUI(0); //0 for Login setup, 1 for Register setup
}

/**
 * @brief LoginWindow::setupUI
 * @param isLogin
 *
 * This displays the login window to the user.
 */
void LoginWindow::setupUI(int isLogin){
    LoginWindow::setWindowTitle("Login/Register");

    setStyleSheet("background-color: #F5EFFF;");
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window

    // Apply styles to buttons
    QString buttonStyle = "QPushButton {"
                          "background-color: #E9A5F1;"
                          "border-radius: 15px;"
                          "color: white;"
                          "border: 2px solid #DD8DF5;"
                          "padding: 10px;"
                          "font-size: 16px;"
                          "font-weight: bold;"
                          "min-width: 300px;"
                          "min-height: 50px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #C68EFD;"
                          "border: 2px solid #924AEB;"
                          "}";

    QString textStyle= "QLineEdit, QLabel { color: purple; }";

    mainTitle = new QLabel("LOGIN", this);
    mainTitle->setStyleSheet("QLabel { color: #924AEB; }");
    if (isLogin==0){
        mainSubtitle = new QLabel("Welcome back! Log in to continue.", this);
        mainSubtitle->setStyleSheet(textStyle);
    } else if (isLogin==1){
        mainSubtitle = new QLabel("New here? Create your account today!", this);
        mainSubtitle->setStyleSheet(textStyle);
    }

    usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Enter your username");
    usernameInput->setFixedSize(300, 40);
    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Enter your password");
    passwordInput->setFixedSize(300, 40);
    usernameInput->setStyleSheet(textStyle);
    passwordInput->setStyleSheet(textStyle);

    login_button = new QPushButton("LOGIN", this);
    login_button->setStyleSheet(buttonStyle);
    login_button->setFixedSize(300, 50);

    create_button = new QPushButton("CREATE ACCOUNT", this);
    create_button->setStyleSheet(buttonStyle);
    create_button->setFixedSize(300, 50);

    if (isLogin==1){
        firstnameInput = new QLineEdit();
        firstnameInput->setPlaceholderText("Enter your first name");
        firstnameInput->setFixedSize(300, 40);
        firstnameInput->setStyleSheet(textStyle);

        lastnameInput = new QLineEdit();
        lastnameInput->setPlaceholderText("Enter your last name");
        lastnameInput->setFixedSize(300, 40);
        lastnameInput->setStyleSheet(textStyle);

        register_button = new QPushButton("REGISTER", this);
        register_button->setStyleSheet(buttonStyle);
        register_button->setFixedSize(300, 50);

        btl_button = new QPushButton("BACK TO LOGIN", this);
        btl_button->setStyleSheet(buttonStyle);
        btl_button->setFixedSize(300, 50);
    }

    login_error = new QLabel("", this);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    layout->addWidget(mainSubtitle, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed));

    if (isLogin==1){
        layout->addWidget(firstnameInput, 0, Qt::AlignHCenter);
        layout->addWidget(lastnameInput, 0, Qt::AlignHCenter);
    }

    layout->addWidget(usernameInput, 0, Qt::AlignHCenter);
    layout->addWidget(passwordInput, 0, Qt::AlignHCenter);

    if (isLogin==1){
        layout->addWidget(register_button, 0, Qt::AlignHCenter);
        layout->addWidget(btl_button, 0, Qt::AlignHCenter);
    } else if (isLogin==0){
        layout->addWidget(login_button, 0, Qt::AlignHCenter);
        layout->addWidget(create_button, 0, Qt::AlignHCenter);
    }

    layout->addItem(new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(login_error, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

    centralWidget->setLayout(layout);

    // Fonts
    QFont maintitleFont("Helvetica", 50, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    QFont mainsubtitleFont("Helvetica", 20, QFont::Medium);
    mainSubtitle->setFont(mainsubtitleFont);

    QFont buttonFont("Helvetica", 16, QFont::Light);
    if (isLogin==1){
        register_button->setFont(buttonFont);
        btl_button->setFont(buttonFont);
    } else if (isLogin==0){
        login_button->setFont(buttonFont);
        create_button->setFont(buttonFont);
    }

    QFont loginerrorFont("Helvetica", 14, QFont::StyleItalic);
    login_error->setFont(loginerrorFont);

    if (isLogin==1){
        connect(register_button, &QPushButton::released, this, &LoginWindow::handleRegister);
        connect(btl_button, &QPushButton::released, this, &LoginWindow::handleBackToLogin);
    }
    connect(login_button, &QPushButton::released, this, &LoginWindow::handleLogin);
    connect(create_button, &QPushButton::released, this, &LoginWindow::handleCreate);
}

/**
 * @brief LoginWindow::handleCreate
 *
 * This is triggered when the user clicks the Create button when making a new user.
 */
void LoginWindow::handleCreate(){
    setupUI(1);
}

/**
 * @brief LoginWindow::handleBackToLogin
 *
 * This is triggered when the user clicks the Login button and thier user account already exists.
 */
void LoginWindow::handleBackToLogin(){
    setupUI(0);
}

/**
 * @brief LoginWindow::handleLogin
 *
 * This is triggered when the user clicks the Back to Login button.
 */
void LoginWindow::handleLogin(){
    DatabaseManager dm;
    dm.connectDatabase();

    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (authenticateUser(username, password)){
        qDebug() <<username <<" logged in successfully!";
        User loggedIn = User(username);
        this->username=loggedIn.getUsername();

        MainWindow *mainScreen = new MainWindow(this);

        mainScreen->username = this->username;
        qDebug() << "Check LoginWindow: " << mainScreen->username;
        mainScreen->showMaximized();
        this->hide();
    } else {
        qDebug() << "Incorrect login information.";
        login_error->setText("Incorrect username or password.");
    }
}

/**
 * @brief LoginWindow::handleRegister
 *
 * This is triggered when the user clicks the Register button.
 */
void LoginWindow::handleRegister(){
    DatabaseManager dm;
    dm.connectDatabase();

    QString firstname = firstnameInput->text();
    QString lastname = lastnameInput->text();
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (insertUser(firstname, lastname, username, password)){
        login_error->setText("User registered successfully!");
        firstnameInput->setText("");
        lastnameInput->setText("");
        usernameInput->setText("");
        passwordInput->setText("");

        setupUI(0); //back to login
    } else {
        login_error->setText("User registration failed.");
    }
}

/**
 * @brief LoginWindow::insertUser
 * @param firstname
 * @param lastname
 * @param username
 * @param password
 * @return
 *
 * This inserts a new user with the provided informaiton in the database.
 */
bool LoginWindow::insertUser(const QString& firstname, const QString& lastname, const QString& username, const QString& password) {
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()){
        qDebug() << "(Login: insertUser) Username availability query failed.";
    }

    if (query.next() && query.value(0).toInt()>0){
        login_error->setText("An account with this username already exists!");
        return false;
    }

    query.prepare("INSERT INTO users (firstname, lastname, username, password) VALUES(:firstname, :lastname, :username, :password)");
    query.bindValue(":firstname", firstname);
    query.bindValue(":lastname", lastname);
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()){
        qDebug() << "(Login: insertUser) Error: " << query.lastError().text();
        return false;
    }

    qDebug() <<"User registration successful!";

    UserFactory uf;
    User newUser = uf.createUser(username);
    newUser.insertHighscore(0);
    newUser.insertLevelscore(0, 0);
    newUser.insertLevelscore(1, 0);
    newUser.insertLevelscore(2, 0);

    qDebug() << "Check: highscore - " << newUser.getHighscore();
    qDebug() << "Check: level 0 - " << newUser.getLevelscore(0);
    qDebug() << "Check: level 1 - " << newUser.getLevelscore(1);
    qDebug() << "Check: level 2 - " << newUser.getLevelscore(2);

    login_error->setText("Success! Account created.");
    return true;
}

/**
 * @brief LoginWindow::authenticateUser
 * @param username
 * @param password
 * @return
 *
 * This method checks the database for a matching username and password.
 */
bool LoginWindow::authenticateUser(const QString& username, const QString& password) {
    QSqlQuery query;

    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()){
        qDebug() << "(Login: authenticateUser) Username retrieval query failed.";
        return false;
    }

    if (query.next()){
        QString dbPass = query.value("password").toString();

        if (dbPass==password){
            qDebug() << "Login successful!";
            login_error->setText("Success! You are logged in.");
        } else {
            qDebug() << "Login failed!";
            login_error->setText("Username and password do not match.");
        }
    }
    return true;
}
