#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#define SCALE_SIZE 3
#define WIDGET_OFFSET 10
#define B_STUDENT_ADJUST studentName->move(line->x(),\
    studentName->y() + (studentName->height() / 2));

#include <QDialog>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QSize>
#include <QPushButton>

class AddStudentDialog: public QDialog{

public:
    AddStudentDialog(QWidget* parent);
    ~AddStudentDialog();

private:
    void scaleWidget(QWidget* widget);
    void positionWidget(QWidget* widget, QWidget* prev);

};

#endif // ADDSTUDENTDIALOG_H
