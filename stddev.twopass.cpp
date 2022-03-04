// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "util.hpp"

int main () {
    //wrapper class to make the size count a bit easier
    //the api should be preserved
    ifwrapper file("test.csv");
    if (!file.is_open()){
        std::cout << "Unable to open file";
        return 1;
    }

    std::cout << "size: " << file.size << " bytes" << std::endl;

    std::string header;
    std::getline(file, header);


    //first pass: calculating the average
    size_t mod = 10000;//report stats every 10k reads

    double sum = 0;
    size_t n = 0;

    std::cout << std::endl;

    std::string line;

    //read the stream line by line
    while(std::getline(file, line)){
        if(n%mod == 0){
            //report stats
            displayProgress("first pass: ",file.getCurrentPosition(), file.size);
        }
        // parsing the line
        double a,b;
        parseLine(line, a, b);

        //calculating the stddev of the first field
        sum += a;
        n++;
    }

    double avg = sum/n;

    //resetting the stream for the next pass
    file.clear();
    file.seekg(0);
    std::getline(file, header);

    //second pass: calculating the sum of squared difference
    double sumsqdiff = 0;
    n = 0;

    std::cout << std::endl;

    while(std::getline(file, line)){
        if(n%mod == 0){
            //report stats
            displayProgress("second pass: ",file.getCurrentPosition(), file.size);
        }
        // parsing the line
        double a,b;
        parseLine(line, a, b);

        //calculating the stddev of the first field
        double diff = a-avg;
        sumsqdiff += diff*diff;
        n++;
    }

    double stddev = sqrt(sumsqdiff/n);

    std::cout << "stddev of the first field is: " << stddev << '\n';
}