#include <stdio.h>

#define SAMPLES 100
#define MATSIZE 1025

int mat[MATSIZE][MATSIZE];

void transpose()
{
    int i, j, aux;

    for (i = 0; i < MATSIZE; i++) {
        for (j = 0; j < MATSIZE; j++) {
            aux = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = aux;
        }
    }
}

int main(void)
{
    int i, j;

    for (i = 0; i < MATSIZE; i++) {
        for (j = 0; j < MATSIZE; j++) {
            mat[i][j] = i + j;
        }
    }

    for (i = 0; i < SAMPLES; i++) {
        transpose();
    }

    return 0;
}
/*
g++ test.cpp
time ./a.out
*/