/**
* @file tutorial.h
* @author Fiona Luo
* @date March 30, 2025
* @brief Header file for the tutorial window.
*/

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class MainWindow;  // Forward declaration

/**
 * @brief The Tutorial class
 *
 * This is the class for tutorial.
 */
class Tutorial : public QWidget {
    Q_OBJECT

    /**
 * @brief Tutorial
 * @param mainWindow
 * @param parent
 *
 * This makes a tutorial window.
 */
public:
    explicit Tutorial(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~Tutorial();

signals:
    /**
     * @brief backToMenu
     *
     * This makes a signal for back to menu.
     */
    void backToMenu();

private:
    QVBoxLayout *layout;
    QLabel *tutorialImage;
    QPushButton *closeButton;
    MainWindow *mainWindow;  // Pointer to MainWindow
};

#endif // TUTORIAL_H
