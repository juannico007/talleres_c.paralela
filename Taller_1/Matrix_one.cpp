#include"Matrix_one.hpp"

MatrixOne::MatrixOne(int m, int n){

	dimx = n;
	dimy = m;
	array = new int[m*n];

	for (int i = 0; i < m*n; i++)
		array[i] = 1;

}

MatrixOne::~MatrixOne(){
	delete []array;
}

MatrixOne& MatrixOne::operator=(MatrixOne& M){
	int x = M.get_dimx(), y = M.get_dimy();
	if(dimx != x || dimy != y){
		dimx = x;
		dimy = y;
		delete[] array;
		array = new int[x*y];
	}
  int size = x*y;
  for(int i = 0; i < size; i++)
    array[i] = M.array[i];
	return *this;
}

void MatrixOne::display(){
  for(int y = 0; y < dimy; y++){
    for(int x = 0; x < dimx; x++)
      printf("%d", array[y * dimx + x]);
		printf("\n");
  }
}
