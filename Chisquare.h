#pragma once

#include"Distribution.h"
#include"Sample.h"

class Chisquare {
	int n, df;
	int* empirical_freq;
	double* theor_probabilities;
public:
	Chisquare(Distribution& d, Sample& s);
	double Calc_chi2(double*t=nullptr);
	~Chisquare();
	void change_sample(Sample& s);
};