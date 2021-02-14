#ifndef MATRIX_ONE
#define MATRIX_ONE

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class MatrixOne{

  private:
    int *array;
    int dimx;
    int dimy;

  public:
	//constructor and destructor
    MatrixOne(int m, int n);
    ~MatrixOne();

	//getters
    int get_dimx() { return dimx; }
    int get_dimy() { return dimy; }
    int get(int x, int y) { return array[y * dimx + x]; }

	//setters
    void set(int x, int y, int val) {array[y * dimx + x] = val;}

	//displayers
    void display();

	//overloads
    MatrixOne& operator=(MatrixOne& M);		//assignment overload

	
};

	MatrixOne operator*( MatrixOne& M1 , MatrixOne& M2 ) ;	

#endif
