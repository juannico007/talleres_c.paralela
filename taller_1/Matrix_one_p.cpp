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
		init( ref(array), 0, m*n);

	}else{								//caso paralelo

		vector<thread> threads;					//vector de hilos
		int partition = (m*n)/threadsNum;		//tamaño de cada pedazo del array que
												//corresponde acada hilo

		for (int t = 0; t < threadsNum; t++){	//inicialización de los procesos
			int start = t*partition;
			int end = t < threadsNum - 1? start+partition : m*n;

			threads.emplace_back(thread(init, ref(array), start, end));
		}

		init(array, 0, partition);

		for (int t = 0; t < threadsNum; t++){

			if	(threads[t].joinable())
				threads[t].join();
		}
	}
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
		cerr << "Multiplication: Matrix dimensions are not compatible!\n";
	}

	int y = M1.get_dimy(), x = M2.get_dimx();
	int size = y*x;

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
