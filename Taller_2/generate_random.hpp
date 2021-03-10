#ifndef __GENERATE_RANDOM_HPP
#define __GENERATE_RANDOM_HPP

#include <fstream>
#include <cstdio>
#include <random>
#include <set>
using namespace std;

void print_vector(long size, const long* a);

void write_vector(long size, const long* a);

void read_vector(long size, long* a);

void generate_vector(long size, long* a, unsigned seed);

void generate_norepeat_vector(long size, long* a, unsigned seed);

#endif
