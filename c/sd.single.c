#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(){
    char* path = "../test.csv";
    FILE* file = fopen(path,"r");
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    //skip the first line (header)
    char* header = NULL;
    size_t headercap = 0;
    getline(&header, &headercap, file);

    size_t n = 0;
    double sum = 0;
    double sumsq = 0;
    fprintf(stderr,"\n");
    while(1){
        if(n%10000 == 0){
            fprintf(stderr,"\033[Fprogress: %f%%\n",((float)(ftell(file)))/(float)size*100);
        }

        double a,b;
        char c;
        //when trailing new line
        if(fscanf(file,"%lf", &a) != 1){
            break;//eof
        }
        fscanf(file,"%c", &c);//comma
        fscanf(file,"%lf", &b);

        sum += a;
        sumsq += a*a;
        n++;


        //no trailing newline
        if(fscanf(file,"%c", &c) != 1){
            break;//eof
        }
    }
    fclose(file);

    double mean = sum / n;
    double variance = sumsq / n - mean * mean;
    double stddev = sqrt(variance);
    printf("sd of the first field: %f\n",stddev);
}










