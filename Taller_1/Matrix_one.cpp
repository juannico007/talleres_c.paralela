
MatrixOne::MatrixOne(int m, int n){

	dimx = m;
	dimy = n;	
	array = new int[m*n];

	for (int i = 0; i < m*n; i++)
		array[i] = 1;

}

MatrixOne::~MatrixOne(){
	delete []array;
}



