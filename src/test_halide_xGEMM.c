#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Initializing  matrices  a, b and c
    // It's a matrices multiplication  so
    // the constraints on dimensions are:
    // A(n,m) B(m,l) C(n,l), alpha & beta
    // can be any real number.

    // Note that they must be the same as 
    // the ones in the Halide program, so
    // we'll get the same results.

    int a[2][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7}};

    int b[4][5] = {
        {0, 1, 2, 3, 5},
        {4, 5, 6, 7, 5},
        {8, 9, 10, 11, 5},
        {8, 9, 10, 11, 5}};

    int c[2][5] = {
        {0, 1, 2, 3, 1},
        {4, 5, 6, 7, 1},
    };

    int alpha = 2, beta = 3;

    // Calucating dimensions
    int x = sizeof(a) / sizeof(a[0]);
    int y = sizeof(a[0])/sizeof(a[0][0]);
    int z = sizeof(b[0])/sizeof(b[0][0]);

    // Openning the results file
    FILE *fptr;
    if ((fptr = fopen("./bin/data/results.txt", "r")) == NULL)
    {
        printf("Error opening file, make sure the results.txt file exists in data directory !");
        exit(1);
    }
    char line[128];
    int calculated_result, stored_result;
    int success = 1;

    // Calculating the product of the matrices 
    // and checking results  at  the same time
    printf("Reading and checking results ...\n");
    for (int i = 0; i < x; i++)
        for (int j = 0; j < z; j++)
        {
            calculated_result = 0;
            for (int k = 0; k < y; ++k)
                calculated_result += a[i][k] * b[k][j];
            calculated_result = alpha * calculated_result + beta * c[i][j];
            fgets(line, 128, fptr);
            stored_result = atoi(line);
            if (calculated_result != stored_result)
            {
                printf("%d is False, that should be : %d\n", stored_result, calculated_result);
                success = 0;
            }
        }
    if (success)
    {
        printf("The multiplication with Halide is working well.\n");
    }
    else
    {
        printf("There are some problems with Halide multiplication.\n");
    }

    return 0;
}