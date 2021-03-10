#include "merge_ser.hpp"

DinArray::DinArray(long size, int type, string name){
  p = new long[size];
  sz = size;
  if(type == 1){
    fill_arr();
  }
  else if (type == 2){
    fill_non_rep_arr();
  }
  else if (type == 3){
    copy_vector(name);
  }
}


DinArray::~DinArray(){
  delete[] p;
}

void DinArray::fill_arr(){
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

void DinArray::display(){
  printf("[");
  for(int i = 0; i < sz - 1; i++){
    printf("%d", p[i]);
  }
  printf("%d]\n", p[sz - 1]);
}
