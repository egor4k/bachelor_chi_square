#include"pch.h"
#include"Chisquare.h"

Chisquare::Chisquare(Distribution& d, Sample& s) {
	n = s.get_n();
	df = s.get_df();
	empirical_freq = new int[df];
	theor_probabilities = new double[df + 1]{ 0 };
	double sum = 0;
	for (int i = 0;i < df;++i) {
		empirical_freq[i] = s.empirical_freq[i];
		theor_probabilities[i] = d.get_probability(i);
		theor_probabilities[df] += theor_probabilities[i];
	}
	theor_probabilities[df] = 1 - theor_probabilities[df];
}

double Chisquare::Calc_chi2(double*t) {
	int* ag = new int[df + 1]{ 0 };
	double* Pg = new double[df + 1]{ 0 };
	int j = 0;
	for (int i = 0;i < df;++i)
		for (;(n * Pg[i] < 5) && (j < df);++j) {
			Pg[i] += theor_probabilities[j];
			ag[i] += empirical_freq[j];
		}
	for (int i = df;i >= 1;--i)
		if (n * Pg[i] < 5) {
			ag[i - 1] += ag[i];
			Pg[i - 1] += Pg[i];
			ag[i] = Pg[i] = 0;
		}
	for (j = 0;Pg[j] && (j < df + 1);++j);
	df = j;
	double sum (0);
	for (int i = 0;i < df;++i) {
		double sizeP = n * Pg[i];
		sum += (ag[i] - sizeP) * (ag[i] - sizeP) / Pg[i];
	}
	sum /= n;
	if (t)
		*t = sum;
	delete[]ag;
	delete[]Pg;
	return 1-pChi(sum, df - 1);
}

Chisquare::~Chisquare() {
	delete[]empirical_freq;
	delete[]theor_probabilities;
	empirical_freq = nullptr;
	theor_probabilities = nullptr;
	n = df = 0;
}

void Chisquare::change_sample(Sample& s)
{
	// TODO: Add your implementation code here.
	delete[]empirical_freq;
	n = s.get_n();
	df = s.get_df();
	empirical_freq = new int[df];
	double sum = 0;
	for (int i = 0; i < df; ++i)
		empirical_freq[i] = s.empirical_freq[i];
}
