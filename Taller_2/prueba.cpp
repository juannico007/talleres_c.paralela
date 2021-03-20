#include<fstream>
#include<iostream>

using namespace std;

int main(){
  ofstream Out("a_ver_que_pdo.dat");
	Out << "veamos";
	Out << "\n";
	Out.close();
}
