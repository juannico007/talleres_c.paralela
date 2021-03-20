#include"merge_ser.hpp"
#include"helper.hpp"

using namespace std;

int main(int argc, char **argv){

	int n = atoi(argv[1]);
	int ntimes = atoi(argv[2]);
	string name = "vector_" + to_string(n) + ".dat";

	vector<double> times;

	for (int i = 0; i < ntimes; i++){
		DinArray arr(n, 3, name);

		DinArray arr2(n, 4);

		double strt = omp_get_wtime();
			merge_sort(arr, 0, arr.size(), arr2);
		double end = omp_get_wtime();

		double partial_time = end - strt;
		times.pushback(partial_time);
	}

	return 0;
}
