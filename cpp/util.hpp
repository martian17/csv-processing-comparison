#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>


size_t filesize(const char *path){
    std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);
    return file.tellg();
}


void displayProgress(const char *msg, double n1, double n2){
    std::cout <<
              "\033[F" << msg << ": " <<
              std::setprecision(4) << (n1/n2*100) <<
              "%               \n";
}


char IfBuffer[60000];

//keeps track of the filesize etc
class ifwrapper : public std::ifstream{
public:
    size_t size;
    size_t start;
    ifwrapper(const char *path): std::ifstream(path) {
        this->rdbuf()->pubsetbuf(IfBuffer, 60000);
        size = filesize(path);
        start = tellg();
    }
    size_t getCurrentPosition(){
        return (size_t)tellg() - start;
    }
};

void parseLine(std::string &line, double &a, double &b){
    // put the line in an istringstream for extraction:
    std::istringstream ss(line);
    // dummy character
    char delim;
    ss >> a >> delim >> b;
}