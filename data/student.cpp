#include "student.h"

/*
 * Conventional implementation
 * I get the urge to break convention
 * and put everything in one header file ;)
 */

//I always forget to redefine extern variables...
std::vector<appstate::STUDENT*> appstate::studentList;

void appstate::initStudentList(){
    using namespace appstate;
    STUDENT* student = new STUDENT{ UNINITIALIZED_ID, (char*) UNINITIALIZED_NAME, false };
    studentList.push_back(student);
}

void appstate::printStudents(){
    using namespace std;
    using namespace appstate;
    for(vector<STUDENT*>::iterator it = studentList.begin(); it != studentList.end(); ++it){
        cout << (*it)->name << endl;
        cout << "Has paid: " << (*it)->paid << endl;
    }
}

/*
 * Converts QString and returns a char*:
 * Much better for serialization
*/
char* appstate::qstringToCstring(QString string){
    QByteArray byteArray = string.toLatin1();
    char* byteDataPayload = byteArray.data();
    return byteDataPayload;
}

/*
 * Insert a new student into the app's state and
 * return a pointer to that student
 */
appstate::STUDENT* appstate::insertStudent(char* studentName){
    using namespace appstate;
    int newId = 0;

    if(!studentList.empty()){
        STUDENT* lastStudent = studentList.back();
        newId = lastStudent->id + 1;
    }

    for(std::vector<STUDENT*>::iterator it = studentList.begin(); it != studentList.end(); ++it){
        std::cout << "From vector: " << (*it)->name << std::endl;
    }

    STUDENT* newStudent = new STUDENT();
    newStudent->id = newId;
    newStudent->paid = false;
    newStudent->name = (char*) malloc((strlen(studentName) + 1) * sizeof(char));
    strcpy(newStudent->name, studentName);
    studentList.push_back(newStudent);
    std::cout << studentName << " inserted into app state" << std::endl;
    return newStudent;
}

int appstate::getStudentCount(){
    return appstate::studentList.size();
}

int appstate::removeStudent(int id){
    using namespace appstate;
    int removedId = -1;

    qDebug() << "Passed id: " << id;

    for(size_t i = 0; i < studentList.size(); i++){
        STUDENT* stdPtr = studentList.at(i);
        if(stdPtr->id == id){
            removedId = stdPtr->id;
            qDebug() << "Removing " << stdPtr->name;
            studentList.erase(studentList.begin() + i);
        }
    }

    if(removedId == -1){
        throw std::invalid_argument("Not a valid student removed");
        exit(-1);
    }

    return removedId;
}

appstate::STUDENT* appstate::getStudentById(int id){
    using namespace appstate;
    STUDENT* student = 0;
    for(size_t i = 0; i < studentList.size(); i++){
        STUDENT* stdPtr = studentList.at(i);
        if(stdPtr->id == id){
            student = stdPtr;
        }
    }
    return student;
}

bool appstate::toggleCheckedState(int id, bool isChecked){
    STUDENT* student = getStudentById(id);
    student->paid = !isChecked;
    return !isChecked;
}
