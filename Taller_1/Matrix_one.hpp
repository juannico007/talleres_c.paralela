#ifndef MATRIX_ONE
#define MATRIX_ONE

class MatrixOne{
  private:
    int *array;
    int dimx;
    int dimy;

  public:
    MatrixOne(int m, int n);
    ~MatrixOne();

    int get_dimx() { return dimx; }
    int get_dimy() { return dimy; }
    int get(int x, int y) { return array[y * dimx + x]; }
    void set(int x, int y, int val) {array[y * dimx + x] = val;}

    MatrixOne& operator=(MatrixOne& M);
    void display();
};
#endif
