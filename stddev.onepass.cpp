// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

size_t filesize(std::string path){
    std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);
    return file.tellg();
}

std::string display_percentage(double n1, double n2){
    float ratio = (float)n1/(float)n2*100;
    char buff[100];
    gcvt(ratio, 6, buff);
    bool terminated = false;
    int decimal = 5;
    for(int i = 0; i < decimal; i++){
        if(buff[i] == '\0'){
            terminated = true;
        }
        if(terminated){
            //fill 0
            buff[i] = '0';
        }
    }
    buff[decimal] = '\0';
    return (std::string) buff;
};

void displayProgress(std::string msg, double n1, double n2){
    std::cout <<
    "\033[F" << msg << ": " <<
    display_percentage(n1,n2) <<
    "%               " << std::endl;
}

//keeps track of the filesize etc
class ifwrapper : public std::ifstream{
public:
    size_t size;
    size_t start;
    ifwrapper(std::string path): std::ifstream(path) {
        size = filesize(path);
        start = tellg();
    }
    size_t getCurrentPosition(){
        return (size_t)tellg() - start;
    }
};


void parseLine(std::string line, double* a, double* b){
    // put the line in an istringstream for extraction:
    std::istringstream ss(line);
    // dummy character
    char delim;
    ss >> *a >> delim >> *b;
}


int main () {
    std::string path = "test.csv";
    //wrapper class to make the size count a bit easier
    //the api should be preserved
    ifwrapper file(path);
    if (!file.is_open()){
        cout << "Unable to open file";
        return 1;
    }

    std::cout << "size: " << file.size << " bytes" << std::endl;

    std::string header;
    std::getline(file, header);


    size_t mod = 10000;//report stats every 10k reads

    double sum = 0;
    double sqsum = 0;
    size_t n = 0;

    std::cout << std::endl;
    //read the stream line by line
    for(std::string line; std::getline(file, line); ){
        if(n%mod == 0){
            //report stats
            displayProgress("progress",file.getCurrentPosition(), file.size);
        }
        // parsing the line
        double a,b;
        parseLine(line,&a,&b);

        //calculating the stddev of the first field
        sum += a;
        sqsum += a*a;
        n++;
    }
    double mean = sum / n;
    double variance = sqsum / n - mean * mean;
    double stddev = sqrt(variance);
    std::cout << "stddev of the first field is: " << stddev << std::endl;



    //apparently, file.close is not needed
    //file.close();
    
    return 0;
}