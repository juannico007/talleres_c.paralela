#include "helper.hpp"

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
