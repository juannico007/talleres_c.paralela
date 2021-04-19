#include "highway.hpp"

int main(int argc, char** argv){
	int N = atoi(argv[1]); 
	Highway carretera(N, 0.75);
	carretera.print_highway();
	for(int i = 0; i < 5; i++){
		carretera.update_state();
		carretera.print_highway();
	}
}
