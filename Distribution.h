#pragma once

#include"PROBDIST.H"
#include<cmath>

const double eps = 1e-9;

class Distribution {
	double p;
	int k;
public:
	Distribution(double _p = 0.5);
	//Distribution(Distribution& d);
	double get_p();
	double set_p(double _p);
	int get_k();
	double get_probability(int i);
	~Distribution();
};