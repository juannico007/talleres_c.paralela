#include <sys/time.h>
#include <mpi.h>
#include <cstdio>
#include<iostream>

#include "pgmio.hpp"
#include"helper.hpp"

using namespace std;



int main(int argc, char** argv){

	string filename;		//string to save filename to be read
	filename.assign(argv[1]);
	string filename2(argv[1]);
	
	// for used to delete the '.pgm' from the string
	for(int i = 0; i < 4; i++){
		filename2.pop_back();
	}

	filename2 += "_re.pgm";

	if(argc == 4){
		filename2 = argv[3];
	}

	printf("%s, %s, %d\n", filename.c_str(), filename2.c_str(), sizeof(argv[1]));

	//get the current number of processes that was passed as an argument to the function
	int nprocesses = atoi(argv[2]);
	string out_name = "results_" + filename + "_" + to_string(n_processes) + ".csv";

	//stream to save the results in a csv file
	ofstream Out(out_name);

	Out << "Mean time, std deviation, reps, size\n";

	
	//allocate buffer
	int m, n;
	pgmsize(filename, m, n);

	cout << "m: " << m << " n: " << n << endl;
	float* buff = new float[m*n];

	/*
		m = number of lines
		n = number of columns
		Keep in mind that we need an extra border (n+2 and m+2)
	*/

	//read image to buff
	pgmread(filename, buff, m, n);

	/* 
 	 * print the matrix of the pgm image
	 */
//
//	for(int i = 0; i < m; i++){
//		for(int j = 0; j < n; j++){
//		  printf(" %.0f", buff[i*n+j]); 
//		}
//		printf("\n");
//	}
	
	vector<int> ntimes = {10, 100, 1000, 10000, 100000};
	vector<double> exec_times(5,0);
	int count = 0;

	for(auto c: ntimes){
		
		/*
		*		Begin of parallel region
		*/
		//Start parallel region and set mpi variables
		MPI_Init(&argc, &argv);
		MPI_Comm comm = MPI_COMM_WORLD;

		int rank, size;
		MPI_Comm_rank(comm, &rank);
		MPI_Comm_size(comm, &size);

		int n_rows = m/size;
		int chunk_size = n_rows*n;
		int chunk_size_halo = (n_rows+2)*(n+2);
		//Initialize receivers for each process, we need a couple of extra columns to comunicate an update correctly every value of the matrix
		float* local_edge = new float[chunk_size];
		float* new_b = new float[chunk_size_halo];
		float* old_b = new float[chunk_size_halo];
		
		double t_start = MPI_Wtime();


		MPI_Scatter(buff, chunk_size, MPI_FLOAT, local_edge, chunk_size, MPI_FLOAT, 0, comm);


	/*
	 *	verify scatter of buffer
	 */	
	//	printf("Im process number %d of %d and I received from %d to %d, I recieved \n ", rank, size, rank*chunk_size, (rank + 1)*chunk_size);
	//
	//	for(int i = 0; i < n_rows; i++){
	//		for(int j = 0; j < n; j++){
	//			printf(" %d: %.0f", rank*chunk_size + i*n + j, local_edge[i*n + j]);
	//		}
	//		printf("\n");
	//	}
	//	printf("\n\n");


		
		//Set white halos of old_b and new_b
		if(rank == 0){
			for(int i = 0; i < n + 2; i++){			//Set upper edge
				new_b[i] = 255;
				old_b[i] = 255;	
			}	
		}else if(rank == size - 1){
			for(int i = 0; i < n + 2; i++){			//Set lower edge
				new_b[(n+2)*(n_rows+1) + i] = 255;
				old_b[(n+2)*(n_rows+1) + i] = 255;
			}
		}

		for(int i = 0; i < n_rows+1; i++){
			new_b[i*(n+2)+0] = 255;					//Set left edge
			old_b[i*(n+2)+0] = 255;
			new_b[i*(n+2)+(n+1)] = 255;				//Set right edge
			old_b[i*(n+2)+(n+1)] = 255;				
		}
	}
/*
 *	print for debug
 *
 */

//	for(int i = 0; i < n_rows+2; i++){
//		for(int j = 0; j < n+2; j++){
//			printf(" %d: %.0f", rank, old_b[i*(n+2) + j]);
//		}
//		printf("\n");
//	}
//	printf("\n\n");
//
//	MPI_Barrier(comm);
//	printf("**********************************************************************************\n");


		for(int i = 0; i < n_rows; i++){
			for(int j = 0; j < n; j++){
			  old_b[(i+1)*(n+2)+(j+1)] = local_edge[i*n+j]; 
			}
		}
	/*
	 *	print for debug
	 *
	 */

	//	for(int i = 0; i < n_rows+2; i++){
	//		for(int j = 0; j < n+2; j++){
	//			printf(" %d: %.0f", rank, old_b[i*(n+2) + j]);
	//		}
	//		printf("\n");
	//	}
	//	printf("\n\n");
	//
	//	MPI_Barrier(comm);
	//	printf("**********************************************************************************\n");
	//

		int next_p = rank + 1;
		int past_p = rank - 1;


		//Loop over iterations-------------------------------------
		
		for(int it = 0; it < c; it++){
			//Set communication between processes to share last ando first partition row
			if(rank == 0){
				MPI_Send(&old_b[(n+2)*n_rows], n+2, MPI_FLOAT, next_p, 1, comm);
				MPI_Recv(&old_b[(n+2)*(n_rows+1)], n+2, MPI_FLOAT, next_p, 0, comm, MPI_STATUS_IGNORE);
			}else if(rank == size - 1){
				MPI_Send(&old_b[(n+2)*1], n+2, MPI_FLOAT, past_p, 0, comm);	
				MPI_Recv(&old_b[(n+2)*0], n+2, MPI_FLOAT, past_p, 1, comm, MPI_STATUS_IGNORE);
			}else{
				//Send and receive from past process
				MPI_Send(&old_b[(n+2)*1], n+2, MPI_FLOAT, past_p, 0, comm);	
				MPI_Recv(&old_b[(n+2)*0], n+2, MPI_FLOAT, past_p, 1, comm, MPI_STATUS_IGNORE);
				//Send and receive from next process
				MPI_Send(&old_b[(n+2)*n_rows], n+2, MPI_FLOAT, next_p, 1, comm);
				MPI_Recv(&old_b[(n+2)*(n_rows+1)], n+2, MPI_FLOAT, next_p, 0, comm, MPI_STATUS_IGNORE);
			}
			//get new values (do not update the halo)
			for(int i = 1; i < n_rows+1; i++){
				for(int j = 1; j < n+1; j++){
					new_b[i*(n+2)+j] = (old_b[i*(n+2)+(j-1)]+
					old_b[i*(n+2)+(j+1)]+
					old_b[(i-1)*(n+2)+j]+
					old_b[(i+1)*(n+2)+j]-
					local_edge[(i-1)*n+(j-1)]) / 4;
					}
				}

			//backup the new to the old array (without the halo)
			for(int i = 1; i < n_rows+1; i++){
				for(int j = 1; j < n+1; j++){
					old_b[i*(n+2)+j] = new_b[i*(n+2)+j];

	//Loop over iterations-------------------------------------
	
	for(int it = 0; it < N; it++){
		//Set communication between processes to share last ando first partition row
		
		if(rank == 0){
			MPI_Send(&old_b[(n+2)*n_rows], n+2, MPI_FLOAT, next_p, 1, comm);
			MPI_Recv(&old_b[(n+2)*(n_rows+1)], n+2, MPI_FLOAT, next_p, 0, comm, MPI_STATUS_IGNORE);
		}else if(rank == size - 1){
			MPI_Send(&old_b[(n+2)*1], n+2, MPI_FLOAT, past_p, 0, comm);	
			MPI_Recv(&old_b[(n+2)*0], n+2, MPI_FLOAT, past_p, 1, comm, MPI_STATUS_IGNORE);
		}else{
			//Send and receive from past process
			MPI_Send(&old_b[(n+2)*1], n+2, MPI_FLOAT, past_p, 0, comm);	
			MPI_Recv(&old_b[(n+2)*0], n+2, MPI_FLOAT, past_p, 1, comm, MPI_STATUS_IGNORE);
			//Send and receive from next process
			MPI_Send(&old_b[(n+2)*n_rows], n+2, MPI_FLOAT, next_p, 1, comm);
			MPI_Recv(&old_b[(n+2)*(n_rows+1)], n+2, MPI_FLOAT, next_p, 0, comm, MPI_STATUS_IGNORE);
		}
		printf("info received\n");
		//get new values (do not update the halo)
		for(int i = 1; i < n_rows+1; i++){
			for(int j = 1; j < n+1; j++){
				new_b[i*(n+2)+j] = (old_b[i*(n+2)+(j-1)]+
				old_b[i*(n+2)+(j+1)]+
				old_b[(i-1)*(n+2)+j]+
				old_b[(i+1)*(n+2)+j]-
				local_edge[(i-1)*n+(j-1)]) / 4;
				}
			}
		}
		
		//---------------------------------------------------------


	/*
	 *	Print for debug
	 */
	//	printf("\nTime taken was  %f seconds\n", tstop-tstart);
	//	for(int i = 0; i < n_rows+2; i++){
	//		for(int j = 0; j < n+2; j++){
	//			printf(" %d: %.0f", rank, old_b[i*(n+2) + j]);
	//		}
	//		printf("\n");
	//	}
	//	printf("\n\n");


		for(int i = 0; i < n_rows; i++){
			for(int j = 0; j < n; j++){
			  local_edge[i*n+j] = old_b[(i+1)*(n+2)+(j+1)];  
			}
		}

	printf("iteration number %d\n",it);
	}
	//---------------------------------------------------------

	//	for(int i = 0; i < n_rows; i++){
	//		for(int j = 0; j < n; j++){
	//			printf(" %d: %.0f", rank*chunk_size + i*n + j, local_edge[i*n + j]);
	//		}
	//		printf("\n");
	//	}
	//	printf("\n\n");
	//

		MPI_Gather(local_edge, chunk_size, MPI_FLOAT, buff, chunk_size, MPI_FLOAT, 0, comm); 

		
		double t_end = MPI_Wtime();

		//write image 
		if(rank==0){
		pgmwrite(filename2, buff, m, n);
		}

		//free local arrays	
		delete[] old_b;
		delete[] new_b;
		delete[] local_edge;
		//end parallel region
		MPI_Finalize();
		
		//free edge, old_b and new_b
		//delete[] edge;

		exec_times[count] = t_end - t_start;
	}	

	Out << mean(times) << "," << stdDeviation(times) << "," << ntimes << "," << n*m << "\n";
	cout << "a\n";


	//free buffer
	delete[] buff;
	
	return 0;
}

