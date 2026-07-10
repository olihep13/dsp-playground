#include <cmath>
#include <vector>
#include <complex>
#include "fft.h"
#include "dsp.h"

fft::fft()
{
}

std::vector<std::complex<double>> fft::dft_float(std::vector<double>& time_domain_signal)
{
	const int N = time_domain_signal.size();

	for (int i = 0;i < N;i++)
	{
		time_domain_signal[i] *= .5 - .5 * std::cos((2 * PI * i) / (N - 1)); //hann window
	}

	std::vector<std::complex<double>> frequency_domain_signal;
	frequency_domain_signal.reserve(N);

	for (int k = 0;k < N;k++)
	{
		std::complex<double> sum(0, 0);

		for (int n = 0;n < N;n++)
		{
			std::complex<double> element(
				time_domain_signal[n] * std::cos((2 * PI * k * n) / N), 
				-1 * time_domain_signal[n] * std::sin((2 * PI * k * n) / N));

			sum += element;
		}

		frequency_domain_signal.push_back(sum);
	}

	return frequency_domain_signal;
}