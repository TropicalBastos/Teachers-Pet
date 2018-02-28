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
    STUDENT* student = new STUDENT{ UNINITIALIZED_ID, UNINITIALIZED_NAME, false };
    studentList.push_back(student);
}

void appstate::printStudents(){
    using namespace std;
    using namespace appstate;
    for(vector<STUDENT*>::iterator it = studentList.begin(); it != studentList.end(); ++it){
        cout << (*it)->name << endl;
    }
}

/*
 * Converts QString and returns a char*:
 * Much better for serialization
*/
const char* appstate::qstringToCstring(QString string){
    QByteArray byteArray = string.toLatin1();
    const char* byteDataPayload = byteArray.data();
    return byteDataPayload;
}

/*
 * Insert a new student into the app's state and
 * return a pointer to that student
 */
appstate::STUDENT* appstate::insertStudent(const char* studentName){
    using namespace appstate;
    STUDENT* lastStudent = studentList.back();
    int newId = lastStudent->id + 1;
    STUDENT* newStudent = new STUDENT{newId, studentName, false};
    studentList.push_back(newStudent);
    std::cout << studentName << " inserted into app state" << std::endl;
    return newStudent;
}

int appstate::getStudentCount(){
    return appstate::studentList.size();
}
