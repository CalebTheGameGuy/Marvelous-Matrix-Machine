#pragma once
#include "Vector3D.h"

class Matrix
{
public:
    //Main methods
    Matrix();
    Matrix(int _m, int _n);
    void read();
    void print();
    Matrix multiply(Matrix other);
    Matrix transpose();
    double determinant();
    Matrix inverse();
    Vector3D multiply(Vector3D v);

    //Added Methods
    double determinateTwoByTwo();
    Matrix multiply(float x);

    //Variables
    static const int M = 10;
    static const int N = 10;
    double A[M][N];
    int m; // actual number of rows
    int n; // actual number of columns
};
