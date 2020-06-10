/**
 * This program is an implementation of a BLAS 
 * (Basic Linear Algebra Subprograms)  routine
 * from the  third  level   which  is  general 
 * matrix-matrix multiplication "xGEMM",of the 
 * form     alpha*A*B + beta*C   using Halide.
 */

// Halide header file, it will
// include the rest of  Halide
#include "Halide.h"

// For printf
#include <stdio.h>

// For files
#include <iostream>
#include <fstream>

using namespace std;
using namespace Halide;

int main(int argc, char **argv)
{

    // Initializing  matrices  a, b and c
    // It's a matrices multiplication  so
    // the constraints on dimensions are:
    // A(n,m) B(m,l) C(n,l), alpha & beta
    // can be any real number.

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

    // Declaring a Halide function
    Func multiply;

    // Declaring two Halide variables that
    // are  going  to  be used  as indices
    Var x, y, z;

    // Declaring  3  buffers to
    // store the three matrices
    Buffer<int> inputA(a);
    Buffer<int> inputB(b);
    Buffer<int> inputC(c);

    // Checking that dimensions   are
    // coherant
    if (! ( (inputA.width() == inputB.height()) && (inputA.height() == inputC.height()) && (inputB.width() == inputC.width()) )){
        printf("Matrices dimensions must be of the form A(n,m) B(m,l) C(n,l)\n");
        exit(1);
    }

    // Declaring  a  reduction domain
    // to use it in the sum reduction
    RDom r(0, inputA.width());

    // Defining the Func object to do matrices
    // multiplication  using the sum reduction
    multiply(z, x) = alpha * sum(inputA(r, x) * inputB(z, r)) + beta * inputC(z, x);

    // Realizing the function
    Buffer<int> output = multiply.realize(inputB.width(),inputA.height());
    printf("Multiplication done ...\n");

    // Storing results  into  a file so the
    // C program will be able to check them
    printf("Saving to bin/data/results.txt ...\n");
    ofstream results("./bin/data/results.txt");
    for (int i = 0; i < output.height(); i++)
    {
        for (int j = 0; j < output.width(); j++)
        {
            results << output(j, i) << "\n";
        }
    }
    results.close();
    printf("Saved successfully !\n");

    // Verification of results calculated
    // By the halid program, same role as
    // the C program so it's commented

    /*
    int vrf ;
    for (int i = 0; i < output.width(); i++)
    {
        for (int j = 0; j < output.height(); j++)
        {
            vrf = 0;
            for (int k = 0; k < inputA.width(); k++)
            {
                vrf += a[i][k] * b[k][j];
            }
            vrf = alpha * vrf + beta * c[i][j];
            printf("output[%d][%d] = %d", i, j, output(i, j));
            if (vrf == output(i, j)) printf(" Correct!\n"); else printf(" False! should be : %d\n",vrf);
        }
    }
    */
    return 0;
}
