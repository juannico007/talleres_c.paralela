
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <random>
#include <sys/time.h>
using namespace std;


double gettime() {
  struct timeval tp;
  gettimeofday(&tp, nullptr);
  return tp.tv_sec + tp.tv_usec/(double)1.0e6;
}


int init_road(int *road, int size, float dens, long seed) {
  default_random_engine rng;
  rng.seed(seed);
  uniform_int_distribution<int> uniform(0,size-1);

  for(int i = 0; i < size; ++i)
    road[i] = 0;

  int Ncars = int(round(size*dens));
  int count = Ncars;
  while(count > 0){
    int position = uniform(rng);
    if(road[position] == 0){
      road[position] = 1;
      count--;
    }
  }
  return Ncars;
}

int update(int *old_road, int *road, int size) {
  int moved = 0;
  for(int i = 0; i < size; ++i){
    int prev = (i-1 == -1) ? size-1 : i-1;
    int next = (i+1 == size) ? 0 : i+1;
    if(old_road[i] == 0){
      if(old_road[prev] == 1)
	road[i] = 1;
      else
	road[i] = 0;
    }else{
      if(old_road[next] == 0){
	road[i] = 0;
	moved++;
      }else
	road[i] = 1;
    }
  }
  return moved;
}

float simulation(int size, float dens, long seed, int Niter) {
  printf("Length of road is %d\n", size);
  printf("Number of iterations is %d \n", Niter);
  printf("Target density of cars is %.3f \n", dens);
  
  int* road1 = new int[size];
  int* road2 = new int[size];

  int Ncars = init_road(road1, size, dens, seed);
  float true_dens = float(Ncars) / size;
  printf("dens: %f\n",true_dens);
  
  // //
  // for(int i = 0; i < size; ++i)
  //   printf("%d ",road1[i]);
  // printf("\n");
  // //
  float av_vel = 0;
  int *dummy;
  for(int i = 0; i < Niter; ++i){
    int moved = update(road1, road2, size);
    float vel = float(moved) / Ncars;
    av_vel += vel;

    // //
    // //printf("moved: %d\n",moved);
    // for(int i = 0; i < size; ++i)
    //   printf("%d ",road2[i]);
    // printf("\n");
    // //
    
    dummy = road1;
    road1 = road2;
    road2 = dummy;
  }
  av_vel /= Niter;
  
  delete[] road1;
  delete[] road2;

  return av_vel;
}

int main(int argc, char** argv) {
  int size = atoi(argv[1]);
  float dens = atof(argv[2]);
  long seed = 132;

  int Niter = 10;

  double t_start = gettime();
  float av_v = simulation(size, dens, seed, Niter);
  double t_stop = gettime();

  printf("Average velocity: %f\n",av_v);
  printf("Time: %f s\n",t_stop-t_start);
  
  return 0;
}
