#ifndef MATRIX_ONE
#define MATRIX_ONE

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>
#include <iostream>

using namespace std;

class MatrixOne{
  private:

    int *array;
    int dimx;
    int dimy;
	int threadsNum;

  public:
    MatrixOne(int m, int n, int thr);
    ~MatrixOne();

    int get_dimx() { return dimx; }
    int get_dimy() { return dimy; }
	  int get_threadNum(){ return threadsNum; }
    int get(int x, int y) { return array[y * dimx + x]; }


    void set(int x, int y, int val) {array[y * dimx + x] = val;}

    MatrixOne& operator=(MatrixOne& M);
    void display();
};

void make_chunk(MatrixOne &M, int a, int b, int size, MatrixOne &M1, MatrixOne &M2);

MatrixOne operator*(MatrixOne &M1, MatrixOne &M2);
#endif
