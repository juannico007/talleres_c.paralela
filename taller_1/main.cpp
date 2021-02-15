#include "Matrix_one.hpp"

const int DIMX = 30;
const int DIMY = 50;

int main ( int argc , char ** argv ) {
  int size = atoi(argv [1]) ;

  MatrixOne M1(DIMY , size);
  MatrixOne M2(size , DIMX);
  // M1.display();
  // M2.display();

  double tstart = gettime ();
  MatrixOne R = M1*M2;
  double tstop = gettime ();


  printf("matrix product:\n");
  // R.display ();
  printf(" %d\n",R. get (0 ,0));
  printf(" Time : %f\n", tstop - tstart );

  return 0;
}
