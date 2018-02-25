#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
