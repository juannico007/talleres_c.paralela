#include <sys/time.h>
#include <mpi.h>
#include "pgmio.hpp"
#include <cstdio>

using namespace std;

double gettime(){
	struct timeval tp;
	gettimeofday (&tp, NULL);
	return tp.tv_sec + tp.tv_usec/(double)1.0e6;
}

int main(int argc, char** argv){
	string filename;
	filename.assign(argv[1]);
	string filename2(argv[1]);
	for(int i = 0; i < 4; i++){
		filename2.pop_back();
	}
	filename2 += "_re.pgm";
	int N = atoi(argv[2]);
	if(argc == 4){
		filename2 = argv[3];
	}
	printf("%s, %s, %d\n", filename.c_str(), filename2.c_str(), sizeof(argv[1]));
	
	//allocate buffer
	int m, n;
	pgmsize(filename, m, n);

	cout << "m: " << m << " n: " << n << endl;
	float* buff = new float[m*n];

	//allocate array to store the buffer + halo
	//allocate array old_b
	//allocate array new_b
	/*
		m = number of lines
		n = number of columns
		Keep in mind that we need an extra border (n+2 and m+2)
	*/
	float* edge = new float[(m+2)*(n+2)];
	float* old_b = new float[(m+2)*(n+2)];
	float* new_b = new float[(m+2)*(n+2)];

	//set halos to 255
	for(int j = 0; j < n+2; j++){
		edge[0*(n+2)+j] = 255;			//Set upper edge
	   	edge[(m+1)*(n+2)+j] = 255;		//Set lower edge
		new_b[0*(n+2)+j] = 255;
	   	new_b[(m+1)*(n+2)+j] = 255;
	}
	for(int i = 1; i < m+1; i++){
		edge[i*(n+2)+0] = 255;			//Set left edge
		edge[i*(n+2)+(n+1)] = 255;		//Set right edge
		new_b[i*(n+2)+0] = 255;
		new_b[i*(n+2)+(n+1)] = 255;
	}

	//read image to buff
	pgmread(filename, buff, m, n);

	//copy buff to edge
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
		  edge[(i+1)*(n+2)+(j+1)] = buff[i*n+j]; 
		}
	}

	//Initialize the old_b array
	//Set all values of old_b in 255
	for(int i = 0; i < (m+2)*(n+2); i++){
		 old_b[i] = 255;
	}


	/*
*		Begin of parallel region
*/
	//Start parallel region and set mpi variables
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	int rank, size;
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	int n_rows = (m+2)/size;
	int chunk_size = n_rows*(n+2);
	//Initialize receivers for each process, we need a couple of extra columns to comunicate an update correctly every value of the matrix
	float* local_edge = new float[chunk_size + (n+2)*2];
	float* local_new_b = new float[chunk_size + (n+2)*2];
	float* local_old_b = new float[chunk_size + (n+2)*2];
	

	MPI_Scatter(edge, chunk_size, MPI_FLOAT, &local_edge[n+2], chunk_size, MPI_FLOAT, 0, comm);
	MPI_Scatter(new_b, chunk_size, MPI_FLOAT, &local_new_b[n+2], chunk_size, MPI_FLOAT, 1, comm);
	MPI_Scatter(old_b, chunk_size, MPI_FLOAT, &local_old_b[n+2], chunk_size, MPI_FLOAT, 2, comm);
	
	printf("Im process number %d of %d and I received from %d to %d ", rank, size, rank*chunk_size, (rank + 1)*chunk_size);
	int c, i, end;
	if(rank == 0){
		i = 0;
		end = chunk_size;
	}else{
		i = 1;
		end = chunk_size + 1;
	}
	for(i; i < end; i++){
		c += (local_edge[n + 2 + i] == edge[rank * (n + 2) + i]);
	}
	printf(chunk_size == c ? "correctly copied\n": "there was an error\n");
	

//
//	double tstart = gettime();
//
//	//Loop over iterations-------------------------------------
//	for(int it = 0; it < N; it++){
//		//get new values (do not update the halo)
//		for(int i = 1; i < m+1; i++){
//		  for(int j = 1; j < n+1; j++){
//			new_b[i*(n+2)+j] = (old_b[i*(n+2)+(j-1)]+
//						 old_b[i*(n+2)+(j+1)]+
//						 old_b[(i-1)*(n+2)+j]+
//						 old_b[(i+1)*(n+2)+j]-
//						 edge[i*(n+2)+j]) / 4;
//		  }
//		}
//
//		//backup the new to the old array (without the halo)
//		for(int i = 1; i < m+1; i++){
//		  for(int j = 1; j < n+1; j++){
//			old_b[i*(n+2)+j] = new_b[i*(n+2)+j];
//		  }
//		}
//	}
//	//---------------------------------------------------------
//
//	double tstop = gettime();
//
//	printf("\nTime taken was  %f seconds\n", tstop-tstart);
//
//	//copy old_b back to buff
//	for(int i = 1; i < m+1; i++){
//		for(int j = 1; j < n+1; j++){
//		  buff[(i-1)*n+(j-1)] = old_b[i*(n+2)+j];
//		}
//	}
//
//	//write image 
//	pgmwrite(filename2, buff, m, n);
//

	//free local arrays	
	delete[] local_old_b;
	delete[] local_new_b;
	delete[] local_edge;
	//end parallel region
	MPI_Finalize();

	//free edge, old_b and new_b
	delete[] edge;
	delete[] old_b;
	delete[] new_b;
	//free buffer
	delete[] buff;
	
	return 0;
}

