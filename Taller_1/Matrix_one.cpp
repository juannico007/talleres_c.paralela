
MatrixOne::MatrixOne(int m, int n){

	dimx = m;
	dimy = n;	
	array = new int[m*n];

	for (int i = 0; i < m*n; i++)
		array[i] = 1;

}

MatrixOne::~MatrixOne(){
	delete []array;
}

#include<Matrix_one.hpp>

MatrixOne::MatrixOne& operator=(MatrixOne& M){
  int x = M.get_dimx(), y = M.get_dimy();
  int size = x*y;
  MatrixOne copy(x, y);
  for(int i = 0; i < size; i++)
    copy.array[i] = M.get(dimy/i - 1, i%dimx);
  return copy;
}

MatrixOne::void display(){
  for(int y = 0; y < dimy; y++){
    for(int x = 0; x < dimx; x++)
      printf("%d", array[y * dimx + x])
  }
}



