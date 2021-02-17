#include "helper.hpp"
#include <cstdlib>
#include <cstdio>

double gettime () {
	struct timeval tp ;
	gettimeofday(&tp, NULL) ;

	return tp.tv_sec + tp.tv_usec/(double)1.0e6 ;
}

double mean(vector<double> data){

	double average = 0;

	for(int i = 0; i < data.size(); i++)
		average += data[i]/data.size();


	return average;
}


double stdDeviation(vector<double> data){

	double variance = 0;
	double average = mean(data);

	for(int i = 0; i < data.size(); i++)
		variance += pow( abs(data[i] - average), 2 );

	printf("%f", variance);
	double ans = sqrt(variance/data.size());

	return ans;
}
