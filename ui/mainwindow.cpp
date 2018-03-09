#include "mainwindow.h"
#include "ui_mainwindow.h"

/*** STATIC GLOBAL INSTANCE ***
*Retrieve with getInstance() */
MainWindow* MainWindow::instance;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initialise base GUI
    init();
    renderMainMenu();
    renderAddButton();
    renderResetButton();
    setMenuListeners();

    //Initialise data layer
//    appstate::initStudentList();
//    appstate::printStudents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow* MainWindow::getInstance(){
    return MainWindow::instance;
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

 /* Main window setup */
void MainWindow::init(){
    ui->setupUi(this);
    QAction* actionQuit = ui->actionQuit;
    this->connect(actionQuit, SIGNAL(triggered(bool)), this, SLOT(on_actionQuit_triggered()));
    setWindowTitle("Teacher's Pet");
    setFixedSize(500, 500);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    MainWindow::instance = this;
}

void MainWindow::renderMainMenu(){
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
}

void MainWindow::setMenuListeners(){
    connect(ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotTest()));
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(loadFile()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(on_actionQuit_triggered()));
}

void MainWindow::renderAddButton(){
    int x = (this->width() / 2) - (ui->pushButton->width() / 2);
    int y = this->height() - (ui->pushButton->height() * 1.75);
    ui->pushButton->move(x, y - 45);
}

/** Update UI based on updated data **/
void MainWindow::updateUi(){
    std::cout << "UI TO BE UPDATED" << std::endl;
}

void MainWindow::on_actionQuit_triggered(){
    QUIT_APPLICATION
}

std::vector<appstate::STUDENT*> MainWindow::getStudents(){
    return appstate::studentList;
}

void MainWindow::renderResetButton(){
    QPushButton* resetButton = new QPushButton("Reset Week", this);
    resetButton->show();
    resetButton->move(ui->pushButton->x(), ui->pushButton->y() + 50);
    resetButton->resize(ui->pushButton->size());
    connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(resetButtonClicked()));
}

void MainWindow::resetButtonClicked(){
    int reply;
    reply = QMessageBox::question(this, "Caution",
                                  "Are you sure you wish to reset the payments for this week?",
                                  QMessageBox::No, QMessageBox::Yes);
    if(reply == QMessageBox::Yes){
        DataAdapter* da = DataAdapter::getInstance();
        da->resetPaidCells();
    }
}

void MainWindow::saveFile(){
    QUrl dest = QFileDialog::getSaveFileUrl(this, QString("Save .tp file"), QDir::homePath(), QString("(*.tp)"));
    char* path = dest.toString().toLatin1().data();

    if(std::string(path) == ""){
        return;
    }

    BinarySerializer bs;
    bs.write(path);
}

void MainWindow::loadFile(){
    QUrl dest = QFileDialog::getOpenFileUrl(this, QString("Select .tp file"), QDir::homePath(), QString("(*.tp)"));
    char* path = dest.toString().toLatin1().data();
    DataAdapter* da = DataAdapter::getInstance();
    da->loadData(path);
}

void MainWindow::newFile(){
    DataAdapter* da = DataAdapter::getInstance();
    da->newData();
}
