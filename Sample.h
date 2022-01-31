#pragma once

#include"Distribution.h"
#include<chrono>
#include<random>

extern std::mt19937 generator;

class Sample {
protected:
	int n, k;
public:
	int* empirical_freq;
	Sample(Distribution& d, int _n);
	virtual int simulate_value(double p)=0;
	void simulate_sample(double p);
	void reset_sample();
	int get_n();
	int get_df();
	virtual int get_method() = 0;
	virtual ~Sample();
};