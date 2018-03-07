#include "binaryserializer.h"

BinarySerializer::BinarySerializer() :
    studentList(appstate::studentList){}

void BinarySerializer::write(const char* outPath){
    //buffer is the true output file path
    char buffer[50];
    sprintf(buffer, "%s%s", outPath, EXT);
    vectorBuf = std::vector<vectorBufStruct>();

    //build the vector without pointers but with pure data
    for(std::vector<appstate::STUDENT*>::iterator it = studentList.begin(); it != studentList.end(); ++it){
        using namespace appstate;
        vectorBufStruct vbs;
        STUDENT student = *(*it);
        int id = student.id;
        std::string charStream(student.name);
        bool paid = student.paid;
        vbs.id = id;
        vbs.charStreamName = charStream;
        vbs.paid = paid;
        vectorBuf.push_back(vbs);
    }

    //now begin the serialization process
    uint32_t vSize = vectorBuf.size();
    std::ofstream out(buffer, std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<char*>(&vSize), sizeof(uint32_t));
    unsigned int pos = 0;
    while(pos < vSize){
        vectorBufStruct tmp = vectorBuf.at(pos);
        /* Serialize the sizeables first
         * Order of serialization is as follows:
         * int id
         * bool paid
         * char array (string) name
         * char seperator - seperates each struct
         */
        out.write(reinterpret_cast<char*>(&tmp.id), sizeof(int));
        out.write(reinterpret_cast<char*>(&tmp.paid), sizeof(bool));
        for(unsigned int i = 0; i < tmp.charStreamName.length(); i++){
            std::string tmpString = tmp.charStreamName;
            const char c = tmpString.at(i);
            out.write(&c, sizeof(char));
        }
        out.write(SEPARATOR, sizeof(char));
        pos++;
    }

    out.flush();
    out.close();

}