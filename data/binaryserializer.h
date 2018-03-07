#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#define BUFSIZE 1024
#define SEPARATOR "|"
#define EXT ".tp"

#include <fstream>
#include "student.h"

/*
 * Serializes vectors of student struct pointers
 * into a .tp file and reads .tp files to load into memory
 * and into the app state
 */

class BinarySerializer{

public:
    BinarySerializer();
    void write(const char* outPath);
    //std::vector<appstate::STUDENT*> read(const char* path);

private:
    struct vectorBufStruct{
      int id;
      std::string charStreamName;
      bool paid;
    };
    std::vector<appstate::STUDENT*> &studentList;
    std::vector<vectorBufStruct> vectorBuf;

};

#endif // BINARYSERIALIZER_H
