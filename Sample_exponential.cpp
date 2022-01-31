#include"pch.h"
#include"Sample_exponential.h"

int Sample_exponential::simulate_value(double p) {
	
	std::uniform_real_distribution<double>distr(0., 1.);
	double a(distr(generator));
	//double a(double(rand()) / RAND_MAX);
	if (a < eps)
		return 0;
	return(int(log(a) / log(1 - p)));
}

int Sample_exponential::get_method() {
	return 0;
}