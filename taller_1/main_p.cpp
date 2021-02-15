#include "matrix_one.hpp"
#include "helper.cpp"

const int DIMX = 3;
const int DIMY = 5;

int main ( int argc , char ** argv ) {

	if (argc < 3){

		printf("error, quantity of entered parameters is less than expected\n");
		printf("expected 1 and got: ");
		cout << argc << endl;

		return 0;
	}


	int size = atoi(argv [1]) ;			//conversión del argumento 1 a size
	int nreps = atoi(argv [2]);			//conversión del argimento 2 a numero de repeticiones del main
	vector<double> time(nreps,0);

	for (int reps = 0; reps < nreps; reps++){

		MatrixOne M1(DIMY , size);
		MatrixOne M2(size , DIMX);

	//	M1.display ();
	//	printf("\n");
	//	M2.display ();
	//	printf("\n");

		double tstart = gettime ();
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

	cout << endl;
	cout << mean(time) << ", " << stdDeviation(time)<< ", "<< nreps << ", "<< size << endl;

	return 0;
}
