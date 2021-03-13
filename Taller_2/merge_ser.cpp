#include "merge_ser.hpp"

/*
 * Constructor and destructor
 */

DinArray::DinArray(long size, int type, string name){

	p = new long[size];	//creates the dinamic array of the specified size

	sz = size;			//stores the size in the local variable of the instance


	if(type == 1){	//fills the array using the specified method

		fill_arr();
	}
	else if (type == 2){

		fill_non_rep_arr();
	}
	else if (type == 3){

		copy_vector(name);
	}
	else if (type == 4){

		fill_zero();
	}
}


DinArray::~DinArray(){
	delete[] p;
}

/*
 * Methods for dynamic array initialization
 *
 */

void DinArray::fill_arr(){	//fills the array with a fixed random seed

	minstd_rand0 rng(123);

	const long max_num = sz;

	//Generation of a sequence of (pseudo)random numbers
	rng();

	for(long i = 0; i < sz; ++i){
		long num = long(max_num * ( double(rng()) / rng.max() ));
		p[i] = num;
	}

}

void DinArray::fill_non_rep_arr(){
	minstd_rand0 rng(123);

	const long max_num = 3 * sz;

	//use set to profit from the count method
	std::set< long> numbers;
	//Generation of a sequence of (pseudo)random numbers
	rng();
	long count = 0;

	while(count < sz){

		long num = long(max_num * ( double(rng()) / rng.max() ));

		if(numbers.count(num) == 0){ //if number not in set
			numbers.insert(num);
			p[count] = num;
			count++;
		}
	}
}

void DinArray::fill_zero(){

	for(int i; i < sz; i++)
		p[i] = 0;
}

/*
 * Copy and Write vector methods
 */

void DinArray::copy_vector(string name){
	ifstream In(name);

	for(long i = 0; i < sz; ++i)
		In >> p[i];
	In.close();
}

void DinArray::write_vector(string name){

	ofstream Out(name);
	for(long i = 0; i < sz; ++i)
		Out << p[i] << " ";

	Out << "\n";
	Out.close();
}

/*
 *	Displayer
 */

void DinArray::display(){
  printf("[");

  for(int i = 0; i < sz - 1; i++){
    printf("%d, ", p[i]);
  }

  printf("%d]\n", p[sz - 1]);
}

/*
 *	Merge Sort Algoritm
 */

void merge(DinArray &v, int ini, int fin, DinArray &tmp){

	int mid = (fin + ini)/2;
	int p1 = ini;
	int p2 = mid;
	int pt = ini;

	while (p1 < mid && p2 < fin){
		if(v.get(p1) < v.get(p2)){
		  tmp.set(pt, v.get(p1));
		  p1++;

		}else{
		  tmp.set(pt, v.get(p2));
		  p2++;
		}

		pt++;
	}

	while (p1 < mid){
		tmp.set(pt, v.get(p1));
		pt++;
		p1++;
	}

	while (p2 < fin){
		tmp.set(pt, v.get(p2));
		pt++;
		p2++;
	}
	
	for(int i = ini; i < fin; i++){
		v.set(i, tmp.get(i));
	}
}

void merge_sort(DinArray &v, int ini, int fin, DinArray &tmp){
  int mid = (fin + ini) / 2;

  if(ini < mid){
    merge_sort(v, ini, mid, tmp); //divide
    merge_sort(v, mid, fin, tmp); //divide
    merge(v, ini, fin, tmp);	  //conquer
  }
}
