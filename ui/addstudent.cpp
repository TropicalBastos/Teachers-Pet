#include "addstudent.h"


AddStudent::AddStudent(QWidget *parent):
    QPushButton(parent),
    dialog(0){

    connect(this, SIGNAL(clicked(bool)), this, SLOT(clickListener()));

}

AddStudent::~AddStudent(){
    delete this;
}

void AddStudent::clickListener(){
    qDebug() << "Add student clicked!";
    if(this->dialog != 0){
        qDebug() << "Dialog exists...";
        delete this->dialog;
    }else{
        this->dialog = new AddStudentDialog(this);
        this->dialog->setFixedSize(400, 160);
        this->dialog->show();
    }
}
