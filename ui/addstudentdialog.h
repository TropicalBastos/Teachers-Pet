#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#define SCALE_SIZE 3
#define WIDGET_OFFSET 10
#define B_STUDENT_ADJUST studentName->move(studentText->x(),\
    studentName->y() + (studentName->height() / 2));

#include <QDialog>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QSize>
#include <QPushButton>
#include "../data/student.h"
#include "mainwindow.h"

class AddStudentDialog: public QDialog{

    Q_OBJECT

public:
    AddStudentDialog(QWidget* parent);
    ~AddStudentDialog();

public slots:
    void onAddStudentClick();

private:
    void scaleWidget(QWidget* widget);
    void positionWidget(QWidget* widget, QWidget* prev);
    QLineEdit* studentText;
    QDialog* parent;

};

#endif // ADDSTUDENTDIALOG_H
