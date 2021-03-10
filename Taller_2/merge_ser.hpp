#ifndef _MERGE_SER_HPP
#define _MERGE_SER_HPP

#include <cstdio>
#include <random>
#include <omp.h>
#include <fstream>
#include <set>
#include <string>

using namespace std;

class DinArray{
private:
  long sz;
  long *p;
  void fill_arr();
  void fill_non_rep_arr();
  void copy_vector(string name = "vector.dat");

public:
  DinArray(long size, int type = 3, string name = "vector.dat");
  ~DinArray();
  int size() {return size};
  void display();
  long get(long pos) {return p[pos]};
  void set(long pos, long val) {p[pos] = val};
  void write_vector(string name = "vector.dat");

};


void merge(vector<int> v, int ini, int fin, vector<int> tmp);
void merge_sort(vector<int> v, int ini, int fin, vector<int> tmp);


#endif
