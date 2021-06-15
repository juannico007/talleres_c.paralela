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
	void fill_zero();

public:
	DinArray(long size, int type = 1, string name = "vector.dat");
	~DinArray();
	long size() {return sz;}
	void display();
	long get(long pos) {return p[pos];}
	void set(long pos, long val) {p[pos] = val;}
	void write_vector(string name = "vector.dat");
};


void merge(DinArray &v, int ini, int fin, DinArray &tmp);
void merge_sort(DinArray &v, int ini, int fin, DinArray &tmp);
void t_merge_s(DinArray &v, int ini, int fin, DinArray &tmp);

#endif
