#ifndef _MERGE_SER_HPP
#define _MERGE_SER_HPP

#include<cstdio>
#include<random>
#include<omp.h>
#include <fstream>
#include <set>

using namespace std;

class DinArray{
private:
  long sz;
  long *p;
  void fill_arr();
  void fill_non_rep_arr();
  void fill_zero();
  void copy_vector(long size, const long* a);

public:
  DinArray(long size, int type);
  ~DinArray();
  int size();
  void display();
  long get(long pos, long val);
  long set(long pos, long val);
  void print_vector(long size, const long* a);


};


void read_vector(long size, long* a);
void merge(vector<int> v, int ini, int fin, vector<int> tmp);
void merge_sort(vector<int> v, int ini, int fin, vector<int> tmp);


#endif
