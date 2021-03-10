#include "generate_random.hpp"


void print_vector(long size, const long* a) {
  for(long i = 0; i < size; ++i)
    printf("%ld ",a[i]);
  printf("\n");
}

void write_vector(long size, const long* a) {
  ofstream Out("vector.dat");
  for(long i = 0; i < size; ++i)
    Out << a[i] << " ";
  Out << "\n";
  Out.close();
}

void read_vector(long size, long* a) {
  ifstream In("vector.dat");
  for(long i = 0; i < size; ++i)
    In >> a[i];
  In.close();
}

void generate_vector(long size, long* a, unsigned seed) {
  minstd_rand0 rng(seed);
  
  const long max_num = size;
  //Generation of a sequence of (pseudo)random numbers
  rng();
  for(long i = 0; i < size; ++i){
    long num = long(max_num * ( double(rng()) / rng.max() ));
    a[i] = num;
  }
}

void generate_norepeat_vector(long size, long* a, unsigned seed) {
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
