#include "Matrix_one.hpp"

const int DIMX = 3;
const int DIMY = 5;

int main ( int argc , char ** argv ) {
  int size = atoi(argv [1]) ;

  MatrixOne M1(DIMY , size);
  MatrixOne M2(size , DIMX);
  M1. display ();
  M2. display ();
  //
  printf("\n");

  M2 = M1;
  M2.display();
  // double tstart = gettime ();
  // MatrixOne <int > R = M1*M2;
  // double tstop = gettime ();
  //
  // //R. display ();
  // printf (" %d\n",R. get (0 ,0));
  // printf (" Time : %f\n", tstop - tstart );

  return 0;
}
