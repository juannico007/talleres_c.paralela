#include <iostream>
#include"merge_par.hpp"

using namespace std;

int main(int argc, char **argv){

	int n = atoi(argv[1]);
	DinArray arr(n);
	
	printf("Unordered vector:\n");
	arr.display();

	printf("\n\n\n");
	// arr.display();
	
	DinArray arr2(n, 4);
	arr.write_vector();
	
	double strt = omp_get_wtime();
		merge_sort(arr, 0, arr.size(), arr2);
	double end = omp_get_wtime();

	double tot_time = end - strt;

	printf("time, size, speedup\n %f, %d\n", tot_time, n);

	printf("'ordered' vector:\n");
	arr.display();

	return 0;
}

void readCsv(double& tserial){
    // Create an input filestream
    ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    int val;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);

        // Create a stringstream from line
        stringstream ss(line);

        // Extract each column name
        while(getline(ss, colname, ',')){
            
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, vector<int> {}});
        }
    }
}
