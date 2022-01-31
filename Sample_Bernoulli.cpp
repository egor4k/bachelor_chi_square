#include"pch.h"
#include"Sample_Bernoulli.h"


int Sample_Bernoulli::simulate_value(double p) {
	//std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double>distr(0., 1.);
	for (int i = 0;;++i)
		if (p + distr(generator) > 1)
			return i;
}

int Sample_Bernoulli::get_method() {
	return 1;
}