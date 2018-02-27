#include "addstudentdialog.h"

/*
 *
 * Messy hand coded dialog for adding students
 * I endorse anyone to contribute and refactor
 *
 */

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
    studentText = new QLineEdit(this);
    scaleWidget((QWidget*) studentText);
    studentText->show();
    B_STUDENT_ADJUST
    positionWidget((QWidget*) studentText, (QWidget*) studentName);
    B_STUDENT_ADJUST
    studentName->move(studentName->x(), studentName->y() - WIDGET_OFFSET);

    //final widget for this view I promise
    QPushButton* addStudent = new QPushButton("Add Student", this);
    scaleWidget((QWidget*) addStudent);
    positionWidget((QWidget*) addStudent, (QWidget*) studentText);

    //attach the listener
    connect(addStudent, SIGNAL(clicked()), this, SLOT(onAddStudentClick()));
}

/*
 * Append students to the global app state vector
 */
void AddStudentDialog::onAddStudentClick(){
    using namespace appstate;
    const char* studentName = qstringToCstring(studentText->text());
    std::cout << studentName << std::endl;
    STUDENT newStudent{studentName, false};
    studentList.push_back(newStudent);
    MainWindow::getInstance()->updateUi();
    this->close();
}

AddStudentDialog::~AddStudentDialog(){
    delete this;
}
