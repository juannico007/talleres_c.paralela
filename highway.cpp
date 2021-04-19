#include "highway.hpp"

Highway::Highway(int s, double d){
	spaces = new bool[s];
	size = s;
	density = d;
	velocity = 0;
	initialize_array();
}

Highway::~Highway(){
	delete[] spaces;
}

int Highway::get_size(){
	return size;
}

double Highway::get_velocity(){
	return velocity;
}

double Highway::get_density(){
	return density;
}

int Highway::get_car_number(){
	return int(density*size);
}

void Highway::print_highway(){
	for(int i = 0; i < size; i++){
		spaces[i]? printf(" Taken "):printf(" Available ");
	}
	printf("\n");
}
 


void Highway:: initialize_array(){
	vector<int> v;
	unsigned int seed = 123;
	minstd_rand0 rng(seed);
	generate_norepeat_vector(get_car_number(), v, rng, size-1);
	for(auto i:v)	
		spaces[i] = true;
}

void  Highway::update_state(){
	bool *next_state = new bool[size];
	for(int i = 0; i < size; i++){
		int prev = (i+size-1)%size;
		int next = (i+1)%size; 
		//printf("prev: %d,  next: %d\n", prev, next);
		if(spaces[i]){
			if(spaces[next]){
				next_state[i] = true;
			}else{
				next_state[i] = false;
			}
		}else{
			if(spaces[prev]){
				next_state[i] = true;
			}else{
				next_state[i] = false;
			}
		}
	}
	delete[] spaces;
	spaces = next_state;
}


void generate_norepeat_vector(int size, vector<int>& v, minstd_rand0& rng, int max_num){
	v.clear();
	//use set to profit from the count method
	set<int> numbers;
	//Generation of a sequence of (pseudo)random numbers
	rng();
	int count = 0;
	while(count < size){
		int num = int(max_num * ( double(rng()) / rng.max() ));
		if(numbers.count(num) == 0 && num > 0){ //if number not in set
			numbers.insert(num);
			v.push_back(num);
			count++;
		}
	}
}
