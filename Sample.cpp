#include"pch.h"
#include"Sample.h"

Sample::Sample(Distribution& d, int _n) :n(_n), k(d.get_k()) {
	empirical_freq = new int[k] {0};
}

int Sample::get_df() {
	return k;
}

int Sample::get_n() {
	return n;
}

void Sample::reset_sample() {
	for (int i = 0;i < k;++i)
		empirical_freq[i] = 0;
}

void Sample::simulate_sample(double p) {
	for (int i = 0; i < k; ++i)
		empirical_freq[i] = 0;
	for (int i = 0;i < n;++i) {
		int m = simulate_value(p);
		m = m >= k ? k - 1 : m;
		++empirical_freq[m];
	}
}

Sample::~Sample() {
	delete[]empirical_freq;
	empirical_freq = nullptr;
	n=k = 0;
}
