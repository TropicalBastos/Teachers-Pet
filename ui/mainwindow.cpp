#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* Main window setup */
    ui->setupUi(this);
    QAction* actionQuit = ui->actionQuit;
    this->connect(actionQuit, SIGNAL(triggered(bool)), this, SLOT(on_actionQuit_triggered()));
    setWindowTitle("Teacher's Pet");
    setFixedSize(400, 300);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    menu = new QMenu(ui->toolButton);
    newAction = new QAction(menu);
    openAction = new QAction(menu);
    saveAction = new QAction(menu);
    exitAction = new QAction(menu);
    newAction->setObjectName("New");
    openAction->setObjectName("Open");
    saveAction->setObjectName("Save");
    exitAction->setObjectName("Exit");
    newAction->setText("New");
    openAction->setText("Open");
    saveAction->setText("Save");
    exitAction->setText("Exit");
    menu->addAction(newAction);
    menu->addAction(openAction);
    menu->addAction(saveAction);
    menu->addAction(exitAction);
    ui->toolButton->setMenu(menu);
    connect(ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotTest()));
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(slotTest()));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(slotTest()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(slotTest()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(on_actionQuit_triggered()));

    appstate::initStudentList();
    appstate::printStudents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTest(){

    /* Casts the sender to a pointer of the sender object */
    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());
    QAction* action = qobject_cast<QAction*>(sender());

    if(toolButton){
        /* Render the menu below the drop down */
        menu->show();
        QPoint point = ui->toolButton->mapToGlobal(QPoint(0, 0));
        int xPos = point.x();
        int yPos = point.y() + ui->toolButton->height();
        menu->move(xPos, yPos);
        qDebug() << "Event raised by QToolButton: " << toolButton->objectName();
    }

    if(action){
        qDebug() << "Event raised by QAction: " << action->objectName();
    }

}

std::vector<appstate::STUDENT> MainWindow::getStudents(){
    return appstate::studentList;
}

void MainWindow::on_actionQuit_triggered(){
    QUIT_APPLICATION
}
