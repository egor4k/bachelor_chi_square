#pragma once

#include"Distribution.h"
#include"Sample.h"

class Sample_Bernoulli :public Sample {
public:
	Sample_Bernoulli(Distribution& d, int _n):Sample(d, _n) {};
	int  simulate_value(double p)override;
	int get_method()override;
	~Sample_Bernoulli()override {};
};
