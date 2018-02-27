#include "student.h"

/*
 * Conventional implementation
 * I get the urge to break convention
 * and put everything in one header file ;)
 */

//I always forget to redefine extern variables...
std::vector<appstate::STUDENT> appstate::studentList;

void appstate::initStudentList(){
    using namespace appstate;
    STUDENT student{ UNINITIALIZED, false };
    studentList.push_back(student);
}

void appstate::printStudents(){
    using namespace std;
    using namespace appstate;
    for(vector<STUDENT>::iterator it = studentList.begin(); it != studentList.end(); ++it){
        cout << (*it).name << endl;
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
