#include "merge_ser.hpp"

DinArray::DinArray(long size, int type){
  *p = new long[size];
  sz = size;
}


DinArray::~DinArray(){
  delete[] p;
}

void DinArray::fill_arr(){
  minstd_rand0 rng(seed);

  const long max_num = size;
  //Generation of a sequence of (pseudo)random numbers
  rng();
  for(long i = 0; i < size; ++i){
    long num = long(max_num * ( double(rng()) / rng.max() ));
    a[i] = num;
  }
}

void DinArray::fill_non_rep_arr(){
  minstd_rand0 rng(seed);

  const long max_num = 3*size;
  //use set to profit from the count method
  set<long> numbers;
  //Generation of a sequence of (pseudo)random numbers
  rng();
  long count = 0;
  while(count < size){
    long num = long(max_num * ( double(rng()) / rng.max() ));
    if(numbers.count(num) == 0){ //if number not in set
      numbers.insert(num);
      a[count] = num;
      count++;
    }
  }
}

void

long DinArray::size(){

}
