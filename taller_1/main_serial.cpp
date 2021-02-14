#include "matrix_one_serial.hpp"
#include <iostream>
#include <sys/time.h>
#include <vector>
#include <math.h>

double gettime () {
	struct timeval tp ;
	gettimeofday(&tp, NULL) ;

	return tp.tv_sec + tp.tv_usec/(double)1.0e6 ;
}

double mean(vector<double> data){

	double average = 0;

	for(int i = 0; i < data.size(); i++)
		average += data[i];

	average /= data.size();
		
	return average;
}


double stdDeviation(vector<double> data){

	double variance = 0;
	double average = mean(data);

	for(int i = 0; i < data.size(); i++)
		variance += pow( (data[i] - average), 2 );
		
	variance /= data.size();

	return sqrt(variance);
}



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









