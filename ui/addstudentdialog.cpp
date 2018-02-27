#include "addstudentdialog.h"

void AddStudentDialog::scaleWidget(QWidget* widget){
    QSize size = widget->size();
    int newWidth = size.width() * SCALE_SIZE;
    widget->setFixedWidth(newWidth);
}

void AddStudentDialog::positionWidget(QWidget *widget, QWidget* prev){
    int prevY = prev->y();
    int difference = prevY + widget->height();
    widget->move(widget->width() / 6.5, difference + WIDGET_OFFSET);
}

AddStudentDialog::AddStudentDialog(QWidget *parent):
    QDialog(parent){

    QLabel* studentName = new QLabel("Student Name:", this);
    QFont font("Arial", 16);
    studentName->setFont(font);
    studentName->show();
    QLineEdit* line = new QLineEdit(this);
    scaleWidget((QWidget*) line);
    line->show();
    B_STUDENT_ADJUST
    positionWidget((QWidget*) line, (QWidget*) studentName);
    B_STUDENT_ADJUST
    studentName->move(studentName->x(), studentName->y() - WIDGET_OFFSET);

    //final widget for this view I promise
    QPushButton* addStudent = new QPushButton("Add Student", this);
    scaleWidget((QWidget*) addStudent);
    positionWidget((QWidget*) addStudent, (QWidget*) line);

}

AddStudentDialog::~AddStudentDialog(){
    delete this;
}
