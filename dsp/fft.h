#pragma once

#include <vector>
#include <random>
#include <complex>

class fft
{
public:
	fft();
	std::vector<std::complex<double>> dft_float(std::vector<double>& time_domain_signal);
};