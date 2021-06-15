#include"merge_par.hpp"
#include"helper.hpp"
#include<iostream>

using namespace std;

int main(int argc, char **argv){

	int nthreads;
	#pragma omp parallel
	{
		nthreads = omp_get_num_threads();
	}

	int ntimes = atoi(argv[1]);
	cout << nthreads << "\n";

	string out_name = "results_" + to_string(nthreads) + "_threads.csv";
	ofstream Out(out_name);

	Out << "Mean time, std deviation, reps, size\n";

	vector<int> sizes = {1000, 100000, 10000000};

	for(int i = 0 ; i < sizes.size(); i++){

		vector<double> times;
		int n = sizes[i];
		string name = "vector_" + to_string(n) + ".dat";

		for (int i = 0; i < ntimes; i++){
			DinArray arr(n, 3, name);

			DinArray arr2(n, 4);

			double strt = omp_get_wtime();
				merge_sort(arr, 0, arr.size(), arr2);
			double end = omp_get_wtime();

			double partial_time = end - strt;
			times.push_back(partial_time);
		}

		Out << mean(times) << ", " << stdDeviation(times) << ", " << ntimes << ", " << n << "\n";
		cout << "a\n";


	}
	Out.close();
	return 0;
}
