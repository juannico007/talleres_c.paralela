#ifndef HIGHWAY_HPP
#define HIGHWAY_HPP
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <random>

using namespace std;

class Highway{
	public:
		Highway(int s, double d);
		~Highway();
		int get_size();
		double get_velocity();
		double get_density();
		int get_car_number();
		void print_highway();
		void update_state();

	private:
		bool *spaces;
		int size;
		double density;
		double velocity;
		void initialize_array();
};

void generate_norepeat_vector(int size, vector<int>& v, minstd_rand0& rng, int max_num);


#endif
