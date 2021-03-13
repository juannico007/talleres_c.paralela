#include"merge_ser.hpp"


int main(int argc, char **argv){

	int n = atoi(argv[1]);
	DinArray arr(n);
	
	// arr.display();
	DinArray arr2(n, 4);
	arr.write_vector();
	merge_sort(arr, 0, arr.size(), arr2);
	arr.display();

	return 0;
}
