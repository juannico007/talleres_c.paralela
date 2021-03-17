#include "omp.h"
#include"merge_ser.hpp"

using namespace std;

int main(int argc, char **argv){

	int n = atoi(argv[1]);
	int ntimes = atoi(argv[2]);

	double total_time = 0;

	for (int i = 0; i < ntimes; i++){
		DinArray arr(n);

		DinArray arr2(n, 4);
		arr.write_vector();

		double strt = omp_get_wtime();
			merge_sort(arr, 0, arr.size(), arr2);
		double end = omp_get_wtime();

		double partial_time = end - strt;

		printf("time, size\n %f, %d\n", partial_time, n);
	}

	return 0;
}
