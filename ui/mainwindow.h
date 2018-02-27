#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define QUIT_APPLICATION QCoreApplication::quit();

#include <QMainWindow>
#include <QDebug>
#include <QDesktopWidget>
#include "../data/student.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<appstate::STUDENT> getStudents();

private slots:
    void on_actionQuit_triggered();
    void slotTest();

private:
    QMenu* menu;
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* exitAction;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
