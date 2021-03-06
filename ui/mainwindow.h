#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define QUIT_APPLICATION QCoreApplication::quit();
#define BUTTON_STYLE "QPushButton:hover{ background-color: blue; color: yellow }"

#include <QMainWindow>
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
#include <QMenu>
#include <QTableView>
#include <QFileDialog>
#include "../data/student.h"
#include "../data/dataadapter.h"
#include "../data/binaryserializer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<appstate::STUDENT*> getStudents();
    void updateUi();
    static MainWindow* getInstance();

private slots:
    void on_actionQuit_triggered();
    void slotTest();
    void resetButtonClicked();
    void saveFile();
    void loadFile();
    void newFile();

private:
    QMenu* menu;
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* exitAction;
    Ui::MainWindow *ui;
    void init();
    void renderMainMenu();
    void setMenuListeners();
    void renderAddButton();
    void renderResetButton();
    static MainWindow* instance;
};

#endif // MAINWINDOW_H
