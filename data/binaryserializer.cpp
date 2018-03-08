#include "binaryserializer.h"

BinarySerializer::BinarySerializer() :
    studentList(appstate::studentList){}

void BinarySerializer::write(char* outPath){

    //first convert outpath to correct file format ie. (*.tp) file
    validateFileType(outPath);
    std::cout << "Outpath is" << outPath << std::endl;

    //vector of buffer structures to hold pure data
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
    std::cout << "Saving to: " << outPath << std::endl;
    uint32_t vSize = vectorBuf.size();
    std::ofstream out(outPath, std::ios::out | std::ios::binary);
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
    std::cout << "Saved!" << std::endl;

}

/* Order of deserialization is as follows:
* int id
* bool paid
* char array (string) name
* char seperator - seperates each struct
*/
void BinarySerializer::read(char *path){

    //validate file
    validateFileType(path);

    //truncate studentlist state
    studentList = std::vector<appstate::STUDENT*>();

    std::ifstream in(path, std::ios::in);
    uint32_t vSize = 0;
    in.read(reinterpret_cast<char*>(&vSize), sizeof(uint32_t));
    for(unsigned int i = 0; i < vSize; i++){
        using namespace appstate;
        std::string charStream = "";
        STUDENT* student = new STUDENT();

        //read subsequent properties
        in.read(reinterpret_cast<char*>(&student->id), sizeof(int));
        in.read(reinterpret_cast<char*>(&student->paid), sizeof(bool));

        char buffer = '0';
        while(buffer != '|'){
            in.read(&buffer, sizeof(char));
            if(buffer == '|') break;
            charStream += buffer;
        }

        student->name = (char*) malloc(charStream.length() * sizeof(char));
        strcpy(student->name, charStream.c_str());
        studentList.push_back(student);
    }

    std::cout << "File read: " << path << std::endl;

}

void BinarySerializer::printReadResult(){

    qDebug() << "Printing results of binary read data:";
    for(std::vector<appstate::STUDENT*>::iterator it = studentList.begin(); it != studentList.end(); ++it){
        qDebug() << "Student id: " << (*it)->id;
        qDebug() << "Student name: " << (*it)->name;
    }

}

void BinarySerializer::validateFileType(char* path){
    std::string stringPath(path);

    //remove file:/// prefix
    stringPath.erase(0, PREFIX_LEN);

    std::regex pattern("^.*\\.tp$");
    if(!std::regex_match(stringPath, pattern)){
        stringPath.append(EXT);
    }

    snprintf(path, (stringPath.length() + 1) * sizeof(char), "%s", stringPath.c_str());
}
