//
// Created by Xiao Ma on 3/21/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BINS 50
#define MAX_THREADS 100

void printUsage() {
    printf("Usage: ./seq.c b t filename \n");
    printf("b: the number of bins, the maximum number is %d\n",MAX_BINS);
    printf("t: the number of threads, the maximum number is %d\n",MAX_THREADS);
    printf("filename: the name of the file that contains all floating numbers\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 4) {
        printf("Error: invalid command!\n");
        printUsage();
        exit(-1);
    }
    int binCnt = atoi(argv[1]);
    int threadCnt = atoi(argv[2]);
    char* fileName = argv[3];

    /** real part start time record */
    clock_t real_start_t, real_end_t;
    real_start_t = clock();
    printf("real part start time: %ld\n", real_start_t);

    /** open the input file */
    FILE *fp  = fopen(fileName,"r");
    if (fp == NULL) {
        printf("Error: cannot open the file %s\n", fileName);
        exit(-1);
    }

    /** judge the number of bins and threads */
    if (binCnt <= 0 || binCnt > MAX_BINS ||
    threadCnt <= 0 || threadCnt > MAX_THREADS) {
        printf("Error: invalid number of bins or threads!\n");
        exit(-1);
    }

    /** get the number of nums from the file */
    int numsCnt = 0;
    fscanf(fp,"%d",&numsCnt);
    printf("%d\n",numsCnt);

    /** store all nums in the array */
    double *nums = (double *)malloc(sizeof(double) * numsCnt);
    for (int i = 0; i < numsCnt; i++) {
        fscanf(fp, "%lf ", &nums[i]);
    }

    /** create and initialize the bins array */
    int *bins = (int *)malloc(sizeof(int) * binCnt);
    for (int i = 0; i < binCnt; ++i) {
        bins[i] = 0;
    }

    printf("bin count = %d\n",binCnt);
    double range = 100.0 / binCnt;   // the range of each bin

    clock_t start_t, end_t;
    start_t = clock();
    printf("parallel part start time: %ld\n", start_t);

    /** calculate the number of nums of each bin */
    for (int i = 0; i < numsCnt; ++i) {
        int index = (int) (nums[i] / range);
        bins[index]++;
    }

    end_t = clock();
    printf("parallel part end time: %ld\n", end_t);

    double total_p_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    for (int i = 0; i < binCnt; ++i) {
        printf("bins[%d] = %d\n",i,bins[i]);
    }

    real_end_t = clock();
    printf("real part end time: %ld\n", real_end_t);

    double total_t = (double)(real_end_t - real_start_t) / CLOCKS_PER_SEC;
    printf("total time: %f; parallel time: %f \n", total_t,total_p_t);



}

