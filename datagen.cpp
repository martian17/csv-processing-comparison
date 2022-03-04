#include <iostream>
#include <fstream>
#include <random>

//generates random number between 0 and 1 uniformly
class Rand{
private:
    std::random_device rd;// /dev/random
    std::mt19937 e2;//engine
    std::uniform_real_distribution<double> dist;//distribution pattern
public:
    Rand(): e2(rd()), dist(0,1){}
    double operator()(){
        return dist(e2);
    }
};

int main(){

    Rand rand;
    std::ofstream file("test.csv");

    //header
    file << "field1,field2\n";

    size_t lines = 100000000;

    for(size_t i = 0; i < lines; i++){
        file << rand() << "," << rand() << '\n';
    }
    std::cout << "done\n";
}