#include<limits>
#include<fstream>
#include<string>
#include<iostream>

int main() {
    std::ifstream fin("test.csv");

    if(!fin.is_open()) {
        std::cout << "test.csv not found or openable\n";
        return 0;
    }
    std::string headers[2];
    std::getline(fin, headers[0], ',');
    std::getline(fin, headers[1]);
    fin.ignore(1, '\n');
    std::cout << headers[0] << "," << headers[1] << '\n';

    register double sum;
    register double sqsum;
    register double n = 0;

    double a, b;

    while(fin >> a) {
        sum += a;
        sqsum += a * a;
        fin.ignore(1, ',');
        fin >> b;
        fin.ignore(1, '\n');
        n++;
        // std::cout << a << ',' << b << '\n';
    };

    double mean = sum / n;

    std::cout << '\n' << mean << '\n' << sqsum / n - mean * mean << '\n';
    return 0;
}