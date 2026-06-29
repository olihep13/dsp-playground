#pragma once

#include <vector>
#include <random>

class fft
{
public:
	fft();
	std::vector<std::complex<double>> fft_float(const std::vector<double>& time_domain_signal);
};