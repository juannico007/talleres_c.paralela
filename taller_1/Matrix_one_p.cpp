#include"Matrix_one.hpp"

using namespace std;

void init(int* arr, int start, int end){

	for (int i = start; i < end; i++)
		arr[i] = 1;

}

MatrixOne::MatrixOne(int m, int n, int thr){

	//inicialización de las variables de la clase
	dimx = n;
	dimy = m;
	threadsNum = thr;

	array = new int[m*n];

	if (threadsNum == 1){				//caso serial
		init(array, 0, m*n);

	}else{								//caso paralelo

		vector<thread> threads;					//vector de hilos
		int partition = (m*n)/threadsNum;		//tamaño de cada pedazo del array que corresponde acada hilo
		int start, end;											//inicio y final de cada particion

		for (int t = 0; t < threadsNum; t++){	//inicialización de los procesos
			start = t*partition;
			end = start+partition;

			threads.emplace_back(thread(init, ref(array), start, end));
		}

		init(array, end, n*m);

		for (int t = 0; t < threadsNum; t++){

			if	(threads[t].joinable())
				threads[t].join();
		}
	}
}

//Destructor
MatrixOne::~MatrixOne(){
	delete []array;
}

//Opreador de igualacion
MatrixOne& MatrixOne::operator=(MatrixOne& M){

	//Obtiene las dimensions de la segunda matriz
	int x = M.get_dimx(), y = M.get_dimy();

	//Si las dimensiones son distintas a las de la primera
	//cambia las dimensiones de la primera
	if(dimx != x || dimy != y){
		dimx = x;
		dimy = y;
		delete[] array;
		array = new int[x*y];
	}

	int size = x*y;

	//Iguala los elementos de la matriz
	for(int i = 0; i < size; i++)
		array[i] = M.array[i];

	return *this;
}

//Muestra la matriz
void MatrixOne::display(){

	for(int y = 0; y < dimy; y++){
		for(int x = 0; x < dimx; x++)
			printf("%d", array[y * dimx + x]);
			printf("\n");
	}

}

//Multiplica parte de las matrices M1 y M2 y guarda los resultados en la matriz M
void make_chunk(MatrixOne &M, int a, int b, int size, MatrixOne &M1, MatrixOne &M2){

	int x = M2.get_dimx();
	int k = M1.get_dimx();

	for(int i = a; i < b; i++){

		//Extraigo las coordenadas de la entrada en la matriz
		//correspondiente al indice i
		int xi = i % x;
		int yi = i / x;
		int count = 0;

		//Ejecuta la sumatoria y calcula la entrada
		for(int j = 0; j < k; j++){
			count += M1.get(j, yi) * M2.get(xi, j);
		}

		M.set(xi, yi, count);
	}

}

//Operador de multiplicacion de matrices
MatrixOne operator*(MatrixOne &M1, MatrixOne &M2){

	if( M1.get_dimx() != M2.get_dimy() ){		//revisa si las dimensiones son compatibles

		printf("dimensions m1: %d\n", M1.get_dimx());
		printf("dimensions m2: %d\n", M2.get_dimy());
		throw runtime_error("Multiplication: Matrix dimensions are not compatible!\n");
	}

	//Obtiene las dimensiones de la matriz resultado
	int y = M1.get_dimy(), x = M2.get_dimx();
	int size = y*x;

	//Asigna el numero de hilos para la matriz resultado
	int thr = M1.get_threadNum() < M2.get_threadNum()? M2.get_threadNum() : M1.get_threadNum();
	MatrixOne res(y, x, thr);
	int n = res.get_threadNum();

	vector<thread> threads;

	for(int i = 0; i < n; i++)
		threads.emplace_back(thread(make_chunk, ref(res), i*size/n, (i+1)*size/n, size, ref(M1), ref(M2)));

	make_chunk(res, (n-1)*size/n, size, size, M1, M2);

	for(int i = 0; i < threads.size(); i++)
		threads[i].join();

	return res;
}
