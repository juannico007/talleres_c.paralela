#include <iostream>
#include"merge_par.hpp"

using namespace std;

int main(int argc, char **argv){

	int n = atoi(argv[1]);
	DinArray arr(n);

	// printf("Unordered vector:\n");
	// arr.display();

	printf("\n\n\n");
	// arr.display();

	DinArray arr2(n, 4);
	arr.write_vector();

	double strt = omp_get_wtime();
		merge_sort(arr, 0, arr.size(), arr2);
	double end = omp_get_wtime();

	double tot_time = end - strt;

	printf("time, size, speedup\n %f, %d\n", tot_time, n);

	// printf("'ordered' vector:\n");
	// arr.display();

	return 0;
}
