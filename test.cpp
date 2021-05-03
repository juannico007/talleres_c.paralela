#include<set>
#include<random>

using namespace std;

void fill_non_rep_arr(){
  minstd_rand0 rng(123);
  long sz = 10;
  long *p = new long[10];

  const long max_num = 3 * sz;
  //use set to profit from the count method
  set< long> numbers;
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
  delete[] p;
}

int main(){
  return 0;
}
