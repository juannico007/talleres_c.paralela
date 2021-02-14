#include "matrix_one_serial.hpp"
#include <iostream>

# include <sys/time.h>

double gettime () {
	struct timeval tp ;
	gettimeofday(&tp, NULL) ;

	return tp.tv_sec + tp.tv_usec/(double)1.0e6 ;
}


const int DIMX = 3;
const int DIMY = 5;

int main ( int argc , char ** argv ) {

	if (argc < 2){

		printf("error, quantity of entered parameters is less than expected\n");
		printf("expected 1 and got: ");
		cout << argc << endl;

		return 0;	
	}

	int size = atoi(argv [1]) ;

	MatrixOne M1(DIMY , size);
	MatrixOne M2(size , DIMX);

	M1.display ();
	printf("\n");
	M2.display ();
	printf("\n");

	double tstart = gettime ();
	MatrixOne R = M1*M2;
	double tstop = gettime ();

	R.display ();
	printf("\n");

	M2 = M1;
	M2.display();
	printf("\n");


	printf (" %d\n",R. get (0 ,0));
	printf (" Time : %f\n", tstop - tstart );

	return 0;
}
