#include"merge_ser.hpp"
#include<iostream>
#include<string>

int main(int argc, char** argv){
  int n = atoi(argv[1]);
  DinArray arr(n, 2);
  string name = "vector_" + to_string(n) + ".dat";
  arr.write_vector(name);
  return 0;
}
