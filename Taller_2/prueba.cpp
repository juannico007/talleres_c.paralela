#include<omp.h>
#include<cstdio>

using namespace std;

void print_a(int a){
  int id = omp_get_thread_num();
  printf("thread %d printing %d\n", id, a);
}

int main(){
  #pragma omp parallel
  {
    #pragma omp single
    {
      int a = 0;
      while(a < 8){
        #pragma omp task firstprivate(a)
        {
          print_a(a);
        }
        a++;
      }
    }
  }

  return 0;
}
