#pragma once

#include"Distribution.h"
#include"Sample.h"

class Sample_exponential :public Sample {
public:
	Sample_exponential(Distribution& d, int _n) :Sample(d, _n) {};
	int simulate_value(double p)override;
	int get_method()override;
	~Sample_exponential()override{};
};

