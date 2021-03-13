#include"merge_par.hpp"


int main(int argc, char **argv){

	int n = atoi(argv[1]);
	DinArray arr(n);
  printf("Unordered vector:\n");
  arr.display();

  printf("\n\n\n");
	// arr.display();
	DinArray arr2(n, 4);
	arr.write_vector();
	merge_sort(arr, 0, arr.size(), arr2);
  printf("'ordered' vector:\n");
	arr.display();

	return 0;
}
