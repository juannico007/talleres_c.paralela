#include "Matrix_one.hpp"
#include "helper.hpp"

const int DIMX = 100;
const int DIMY = 100;

int main ( int argc , char ** argv ) {

	/*Verifica que se pasaran todos los argumentos:
	  Numero de columnas del primer vector que es igual al de filas del segundo
		
	*/
	if (argc < 3){
		printf("error, quantity of entered parameters is less than expected\n");
		printf("expected 3 and got: ");
		printf("%d\n", argc);
		printf("expected: size, number of repetitions for stdDeviation and median calculation\n");
		return 0;
	}

	const auto processor_count = std::thread::hardware_concurrency();

	int size = atoi(argv [1]) ;			//conversión del argumento 1 a size
	int nreps = atoi(argv [2]);			//conversión del argumento 2 a numero de repeticiones del main

	/*conversión del argumento 3 a numero entero de hilos
	en caso de que la cantidad de hilos supere la cantidad de hilos disponibles en el computador
	asigna el máximo de hilos posibles para el computador*/

	// int nthreads = atoi(argv[3]) > processor_count? processor_count : atoi(argv[3]);


	for(int nthreads = 1; nthreads <= processor_count; nthreads++){
		vector<double> time;
		for (int reps = 0; reps < nreps; reps++){

			double tstart = gettime ();
			MatrixOne M1(DIMY, size, nthreads);
			MatrixOne M2(size, DIMX, nthreads);

		//	M1.display ();
		//	printf("\n");
		//	M2.display ();
		//	printf("\n");

			MatrixOne R = M1*M2;
			double tstop = gettime ();

		//	R.display ();
		//	printf("\n");

		//	M2 = M1;
		//	M2.display();
		//	printf("\n");


		//	printf (" %d\n",R. get (0 ,0));
		//	printf (" Time : %f\n", tstop - tstart );

			time.push_back(tstop - tstart);
		}

		printf("\n");
		printf("%f, %f, %d, %d, %d, %d\n", mean(time), stdDeviation(time), nreps, DIMY*size, size*DIMX, nthreads);

	}
	return 0;
}
