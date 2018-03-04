#include "resetter.h"

/*
 * Resets payment checked status
 * for all students
 */
void Resetter::reset(){

    using namespace appstate;
    for(std::vector<STUDENT*>::iterator it = studentList.begin(); it != studentList.end(); ++it){
        (*it)->paid = false;
    }

}
