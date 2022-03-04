// reading a text file
#include <iostream>
#include <string>
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

    std::cout << "size: " << file.size << " bytes\n";

    std::string header;

    getline(file, header);

    size_t mod = 10000;//report stats every 10k reads

    double sum = 0;
    double sqsum = 0;
    size_t n = 0;

    std::cout << std::endl;

    std::string line;

    //read the stream line by line
    while(std::getline(file, line)){
        if(n%mod == 0){
            //report stats
            displayProgress("progress", file.getCurrentPosition(), file.size);
        }
        // parsing the line
        double a,b;
        parseLine(line, a, b);

        //calculating the stddev of the first field
        sum += a;
        sqsum += a*a;
        n++;
    }

    double mean = sum / n;
    double variance = sqsum / n - mean * mean;
    double stddev = sqrt(variance);

    std::cout << "stddev of the first field is: " << stddev << '\n';
}