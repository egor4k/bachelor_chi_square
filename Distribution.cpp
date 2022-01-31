#include"pch.h"
#include"Distribution.h"

Distribution::Distribution(double _p) :p(_p) {
	double sum(0);
	for (k = 0; sum < 1 - eps; ++k) {
		sum += _p;
		_p *= 1 - p;
	}
}

//Distribution::Distribution(Distribution& d) {
//	p = d.get_p();
//	double sum = 0;
//	for (k = 0;sum < 1 - eps;++k)
//		sum += get_probability(k);
//}

int Distribution::get_k() {
	return k;
}

double Distribution::get_p() {
	return p;
}

double Distribution::set_p(double _p){
	p = _p;
	double sum = 0;
	for (k = 0; sum < 1 - eps; ++k) {
		sum += _p;
		_p *= 1 - p;
	}
	return p;
}

double Distribution::get_probability(int i) {
	return(p * pow(1 - p, i));
}

Distribution::~Distribution() {
	p = 0;
}
