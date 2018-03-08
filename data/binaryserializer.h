#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#define BUFSIZE 1024
#define SEPARATOR "|"
#define EXT ".tp"
#define PREFIX_LEN 7

#include <fstream>
#include <regex>
#include "student.h"

/*
 * Serializes vectors of student struct pointers
 * into a .tp file and reads .tp files to load into memory
 * and into the app state
 */

class BinarySerializer{

public:
    BinarySerializer();
    void write(char* outPath);
    void read(const char* path);

    //Debug method
    void printReadResult();

private:
    struct vectorBufStruct{
      int id;
      std::string charStreamName;
      bool paid;
    };

    /* Reference to the app state's student list */
    std::vector<appstate::STUDENT*> &studentList;
    std::vector<vectorBufStruct> vectorBuf;
    void validateFileType(char* path);

};

#endif // BINARYSERIALIZER_H
