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

void make_chunk(MatrixOne &M, int a, int b, int size, MatrixOne &M1, MatrixOne &M2){
	int x = M2.get_dimx();
	int k = M1.get_dimx();
	for(int i = a; i < b; i++){
		int xi = i % x;
		int yi = i / x;
		int count = 0;
		for(int j = 0; j < k; j++){
			count += M1.get(j, yi) * M2.get(xi, j);
		}
		M.set(xi, yi, count);
	}
}

MatrixOne operator*(MatrixOne &M1, MatrixOne &M2){
	if( M1.get_dimx() != M2.get_dimy() ){		//revisa si las dimensiones son compatibles
		printf("dimensions m1: %d\n", M1.get_dimx());
		printf("dimensions m2: %d\n", M2.get_dimy());
		throw runtime_error("Multiplication: Matrix dimensions are not compatible!\n");
	}
	int y = M1.get_dimy(), x = M2.get_dimx();
	int size = y*x;
	MatrixOne res(y, x);
	int n = 6;
	vector<thread> threads;
	for(int i = 0; i < n; i++)
		threads.emplace_back(thread(make_chunk, ref(res), i*size/n, (i+1)*size/n, size, ref(M1), ref(M2)));

  make_chunk(res, (n-1)*size/n, size, size, M1, M2);

	for(int i = 0; i < threads.size(); i++)
		threads[i].join();

	return res;
}
