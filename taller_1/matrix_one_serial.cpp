#include "matrix_one_serial.hpp"

MatrixOne::MatrixOne(int m, int n){

	dimy = m;
	dimx = n;
	array = new int[m*n];

	for (int i = 0; i < m*n; i++)
		array[i] = 1;
}

MatrixOne::~MatrixOne(){

	delete []array;
}


void MatrixOne::display(){

  for(int y = 0; y < dimy; y++){

    for(int x = 0; x < dimx; x++){
      printf("%d", array[y * dimx + x]);
	  printf(", ");
	}
	printf("\n");
  }

}

MatrixOne& MatrixOne::operator=(MatrixOne& M){
	int x = M.get_dimx(), y = M.get_dimy();

	if( (dimx != x) or (dimy != y) ){
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

MatrixOne operator*( MatrixOne& M1 , MatrixOne& M2 ){

	if( M1.get_dimx() != M2.get_dimy() ){		//revisa si las dimensiones son compatibles
		cerr << "Matrix dimensions are not compatible!" << endl;
		cout << "dimensions m1: " << M1.get_dimx() <<endl;
		cout << "dimensions m2: " << M2.get_dimy() <<endl;

	}

	//crea la matriz resultante con las dimensiones requeridas
	MatrixOne ans(M1.get_dimy(), M2.get_dimx());	


	for(int y = 0; y < ans.get_dimy(); y++){					//itera en las filas
		for(int x = 0; x < ans.get_dimx(); x++){				//itera en las columnas 
			
			//hasta este punto ya se tiene una pareja ordenada (y,x) -> (fila, columna)
			//de la matriz que se va llenar	(ans)
		
			/*	Ahora procede hacer los productos puntos para dar valor a esa casilla
			 *	de la matriz respuesta
			 */

			int dotProduct = 0;			//contador para almacenar el resultado del producto punto
			int localCol = 0;			//contadores locales para iterar en las columnas
			int localRow = 0;			//contadores locales para iterar en las filas


			for(int n = 0; n < M1.get_dimx(); n++){

				int entry1 = M1.get(localCol, y);	//variable que guarda las entradas de M1
				int entry2 = M2.get(x, localRow);	//variable que guarda las entradas de M2

				dotProduct += entry1 * entry2;
				localCol++;							//se corre hacia a la siguiente columna
				localRow++;							//baja a la siguiente fila
			}
			
			ans.set(x,y,dotProduct);
		}

	}

	return ans;
}





