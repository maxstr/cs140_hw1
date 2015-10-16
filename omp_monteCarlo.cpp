#include <iostream>
#include <stdio.h>
#include <utility>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

std::pair<double, double> throwDart();
double distSquared(std::pair<double, double>);
void Usage(char*);

int main(int argc, char* argv[]) {
    long long int numThrows, inCircle, threadCount, eachThread;
    threadCount = strtol(argv[2], NULL, 10);
    numThrows = strtol(argv[1], NULL, 10);
    double estimatedPI = 0.0;
    if (argc != 3) Usage(argv[0]);
    else if (numThrows % threadCount != 0) Usage(argv[0]);
    inCircle = 0;
    eachThread = numThrows / threadCount;
#   pragma omp parallel num_threads(threadCount) \
    reduction(+: inCircle)
    {
        std::pair<double, double> currentResult = std::make_pair(0, 0);
        for (int i = 0; i <= eachThread; i++) {
            currentResult = throwDart();
            if (distSquared(currentResult) <= 1)
                inCircle += 1;
        }       
    }
    estimatedPI = 4 * ( ((double) inCircle) / ((double) numThrows) );
    printf("Estimated PI Value: %f \n", estimatedPI);
   return 0;
}  /* main */

void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of throws> <number of threads>\n", prog_name);
   fprintf(stderr, "   number of throws must be evenly divisible by\n");
   fprintf(stderr, "   number of threads\n");
   exit(0);
} 

std::pair<double, double> throwDart() {
    double x = (((double) rand() / RAND_MAX) * 2) - 1;
    double y = (((double) rand() / RAND_MAX) * 2) - 1;
    return std::make_pair(x,y); 
}  
double distSquared(std::pair<double, double> coords) {
    return coords.first * coords.first + coords.second * coords.second;
}
