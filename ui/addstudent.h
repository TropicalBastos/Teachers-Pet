#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QPushButton>
#include <QDebug>
#include "addstudentdialog.h"

class AddStudent: public QPushButton{

    Q_OBJECT

public:
    AddStudent(QWidget* parent);
    ~AddStudent();

public slots:
    void clickListener();

private:
    AddStudentDialog* dialog;

};

#endif // ADDSTUDENT_H
