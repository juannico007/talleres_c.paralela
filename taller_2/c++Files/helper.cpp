#include "helper.hpp"

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
		variance += pow(abs(data[i] - average), 2 );

	double ans = sqrt(variance/data.size());

	return ans;
}
