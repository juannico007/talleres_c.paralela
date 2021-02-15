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

//Funcion de asignacion de una matriz
MatrixOne& MatrixOne::operator=(MatrixOne& M){
	int x = M.get_dimx(), y = M.get_dimy();
	/*En caso de que las dimensiones de la matriz a copiar sean distintas
	se cambian las de la antigua
	*/
	if(dimx != x || dimy != y){
		dimx = x;
		dimy = y;
		delete[] array;
		array = new int[x*y];
	}
  int size = x*y;
	//Asigna elemento a elemento
  for(int i = 0; i < size; i++)
    array[i] = M.array[i];
	return *this;
}

//Funcion para mostrar la matriz con las dimensiones correspondientes
void MatrixOne::display(){
  for(int y = 0; y < dimy; y++){
    for(int x = 0; x < dimx; x++)
      printf("%d", array[y * dimx + x]);
		printf("\n");
  }
}

MatrixOne operator*(MatrixOne &M1, MatrixOne &M2){
	if( M1.get_dimx() != M2.get_dimy() ){		//revisa si las dimensiones son compatibles
		printf("dimensions m1: %d\n", M1.get_dimx());
		printf("dimensions m2: %d\n", M2.get_dimy());
		throw runtime_error("Multiplication: Matrix dimensions are not compatible!\n");
	}
	//Crea la nueva matriz y establece las dimensiones para trabajar la funcion
	int y = M1.get_dimy(), x = M2.get_dimx();
	int k = M1.get_dimx();												//Rango del for en la sumatoria
	int size = y*x;
	MatrixOne res(y, x);


	for(int i = 0; i < size; i++){
		/*Decodifica el i-esimo elemento del arreglo matriz en coordenadas (xi, yi)
			para llenar la matriz
		*/
		int xi = i % x;
		int yi = i / x;

		/*Se crea el contador de la sumatoria y
		se hacen los productos puntos de filas y columnas
		*/
		int count = 0;
		for(int j = 0; j < k; j++){
			count += M1.get(j, yi) * M2.get(xi, j);
		}
		res.set(xi, yi, count);
	}
	return res;
}
