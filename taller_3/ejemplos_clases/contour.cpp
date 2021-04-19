#include "pgmio.hpp"

int main(){
  string filename = "perrucho.pgm";
  string filename2 = "edge4896x3264.pgm";
  //initialize 2D dynalloc array
  int m, n;
  pgmsize(filename, m, n);
  cout << "m: " << m << " n: " << n << endl;
  float* data = new float[m*n];

  pgmread(filename, data, m, n);
  
  //contour
  float* new_data = new float[m*n];
  
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < n; ++j){

      if((i>0 && i<m-1) && (i>0 && i<n-1))
	new_data[i*n+j] = data[(i-1)*n+j] + data[(i+1)*n+j] +
	  data[i*n+(j-1)] + data[i*n+(j+1)] - 4*data[i*n+j];
      else
	new_data[i*n+j] = data[i*n+j];
      
    }
  }

  
  pgmwrite(filename2, new_data, m, n);
  
  //delete dynalloc array
  delete[] data;
  delete[] new_data;
  
  return 0;
}
