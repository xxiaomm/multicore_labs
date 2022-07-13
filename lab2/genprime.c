//
// Created by Xiao Ma on 4/4/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define MAX_THREADS 100

void printUsage() {
    printf("Usage:  ./genprime N t \n");
    printf("N: a positive number bigger than 2! \n");
    printf("t: the number of threads and is a positive integer that does not exceed %d.\n",MAX_THREADS);

    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 3) {
        printf("Error: invalid command!\n");
        printUsage();
        exit(-1);
    }
    int N = atoi(argv[1]);
    int threadCnt = atoi(argv[2]);

    /** judge the number of N and threads */
    if (N <= 2 || threadCnt < 0 || threadCnt > MAX_THREADS) {
        printf("Error: invalid number of N or threads!\n");
        exit(-1);
    }

    /**initialize the array which store all prime number */
    int *arrPrime = (int*) malloc(sizeof(int) * (N+1));
    arrPrime[0] = arrPrime[1] = -1;
    for (int i = 2; i < N; ++i) {
        arrPrime[i] = 1;
    }

    /**declare and record the time */
    double t_start, t_end;
    t_start = omp_get_wtime();

    /**implement the parallel part */

    for (int i = 2; i <= (N + 1)/2; ++i) {

//#pragma omp parallel for num_threads(threadCnt)
#pragma omp parallel for schedule(static, 2)
        for (int j = 2*i; j <= N; j=j+i) {
            arrPrime[j] = -1;
        }

    }

    t_end = omp_get_wtime();

    printf("Time take for the main part: %f\n", t_end - t_start);

    /**formalize the file name */
    char *fileName = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 4));
    fileName = argv[1];
    strcat(fileName, ".txt");
//    printf("%s\n",fileName);

    /**write content into the file */
    FILE *fp = fopen(fileName, "w");

    for (int i = 0, j = 1; i < N; ++i) {
        if (arrPrime[i] == 1){
            fprintf(fp,"%d, %d\n",j++, i);
//            printf("%d, %d\n", i, arrPrime[i]);
        }
    }

    fclose(fp);

}