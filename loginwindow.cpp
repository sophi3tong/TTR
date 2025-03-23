#include "loginwindow.h"
#include "mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent):QMainWindow{parent}{
    setupUI(0); //0 for Login setup, 1 for Register setup
}

void LoginWindow::setupUI(int isLogin){
    LoginWindow::setWindowTitle("Login/Register");
    connectDatabase();

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window

    mainTitle = new QLabel("LOGIN", this);
    if (isLogin==0){
        mainSubtitle = new QLabel("Welcome back! Log in to continue.", this);
    } else if (isLogin==1){
        mainSubtitle = new QLabel("New here? Create your account today!", this);
    }
    usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Enter your username");
    usernameInput->setFixedSize(300, 40);
    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Enter your password");
    passwordInput->setFixedSize(300, 40);

    login_button = new QPushButton("LOGIN", this);
    login_button->setFixedSize(300, 50);

    create_button = new QPushButton("CREATE ACCOUNT", this);
    create_button->setFixedSize(300, 50);

    if (isLogin==1){
        firstnameInput = new QLineEdit();
        firstnameInput->setPlaceholderText("Enter your first name");
        firstnameInput->setFixedSize(300, 40);

        lastnameInput = new QLineEdit();
        lastnameInput->setPlaceholderText("Enter your last name");
        lastnameInput->setFixedSize(300, 40);

        register_button = new QPushButton("REGISTER", this);
        register_button->setFixedSize(300, 50);

        btl_button = new QPushButton("BACK TO LOGIN", this);
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

void LoginWindow::handleCreate(){
    setupUI(1);
}

void LoginWindow::handleBackToLogin(){
    setupUI(0);
}

void LoginWindow::handleLogin(){
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (authenticateUser(username, password)){
        qDebug() <<username <<" logged in successfully!";
        UserFactory uf;
        uf.createUser(username);

        //go to level selection
        LevelWindow *levelScreen = new LevelWindow(this);
        levelScreen->showMaximized();
        this->hide();
    } else {
        qDebug() << "Incorrect login information.";
        login_error->setText("Incorrect username or password.");
    }
}

void LoginWindow::handleRegister(){
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
    } else {
        login_error->setText("User registration failed.");
    }
}

void LoginWindow::checkDrivers() {
    qDebug() << "Available drivers: " << QSqlDatabase::drivers();
}

void LoginWindow::connectDatabase(){
    QCoreApplication::addLibraryPath("/usr/local/share/qt/plugins");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("ttr-database.cnm8mega2y8r.us-east-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("ttr_db");
    db.setUserName("admin");
    db.setPassword("TTR**db123");

    checkDrivers();

    if (!db.open()) {
        qDebug() << "Error: Could not open database!" << db.lastError().text();
        return;
    }
    qDebug() << "Database connected successfully!";
}

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
    login_error->setText("Success! Account created.");
    return true;
}

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

            // MainWindow w;
            // w.showMaximized();
            // this->hide();
        } else {
            qDebug() << "Login failed!";
            login_error->setText("Username and password do not match.");
        }
    }
    return true;
}
