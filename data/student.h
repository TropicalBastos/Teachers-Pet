#ifndef STUDENT_H
#define STUDENT_H
#define UNINITIALIZED "$not_initialized$"

#include <vector>
#include <iostream>
#include <QString>
#include <QByteArray>

/**
 * App state is accessed and initialised to 0 here
 * upon opening a .tp file a vector of students is
 * unserialized and stored in the app state
 */

namespace appstate{

typedef struct studentStruct{
    const char* name;
    bool paid;
} STUDENT;

extern std::vector<STUDENT> studentList;
void initStudentList();
void printStudents();
const char* qstringToCstring(QString string);

}


#endif // STUDENT_H