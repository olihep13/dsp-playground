#include <cmath>
#include <vector>
#include "filter.h"
#include <format>
#include "dsp.h"
#include <iostream>

double sinc_helper(double x)
{
	if (std::abs(x) < 1e-8) 
		return 1.0;

	return std::sin(PI * x) / (PI * x);
}

filter::filter(const double& sampleRate, const int& filterSize, const double& cutoffFrequency0, const bool& bandPass, const double& cutoffFrequency1)
{
	this->sampleRate = sampleRate;
	this->filterSize = filterSize;
	this->cutoffFrequency0 = cutoffFrequency0;
	this->cutoffFrequency1 = cutoffFrequency1;
	this->normalizedCutoffFrequency0 = this->cutoffFrequency0 / this->sampleRate;
	this->normalizedCutoffFrequency1 = this->cutoffFrequency1 / this->sampleRate;

	std::cout << "filter size" << (this->filterSize / 2) << std::endl;

	if (bandPass)
	{
		// BANDPASS
		for (int i = 0;i < this->filterSize;i++)
		{
			double index = i - (this->filterSize / 2);
			double signal_value = 0;

			if (index != 0)
			{
				signal_value = 2 * this->normalizedCutoffFrequency1 * sinc_helper(2 * this->normalizedCutoffFrequency1 * index);
				signal_value -= 2 * this->normalizedCutoffFrequency0 * sinc_helper(2 * this->normalizedCutoffFrequency0 * index);
			}
			else
			{
				signal_value = 2 * (this->normalizedCutoffFrequency1 - this->normalizedCutoffFrequency0); // sinc is 1 at 0
				std::cout << "Signal value for bandpass filter: " << signal_value << std::endl;
			}

			signal_value *= .5 - .5*std::cos((2*PI*i)/(this->filterSize-1)); //hann window

			filterSignal.push_back(signal_value);
		}
	}
	else
	{
		// LOWPASS
		for (int i = 0;i < this->filterSize;i++)
		{
			double index = i - (this->filterSize / 2);
			double signal_value = 0;

			if (index != 0)
			{
				signal_value = 2 * this->normalizedCutoffFrequency0 * sinc_helper(2 * this->normalizedCutoffFrequency0 * index);
			}
			else
			{
				signal_value = 2 * this->normalizedCutoffFrequency0; // sinc at 0 is 1
				std::cout << "Signal value for lowpass filter: " << signal_value << std::endl;
				std::cout << "Normalized cutoff frequency: " << this->normalizedCutoffFrequency0 << std::endl;
			}
			
			signal_value *= .5 - .5 * std::cos((2 * PI * i) / (this->filterSize - 1)); //hann window

			filterSignal.push_back(signal_value);
		}

		double sum = 0;

		for (double h : filterSignal)
			sum += h;

		for (double& h : filterSignal)
			h /= sum;

		std::cout << "filter sum " << sum << std::endl;
	}
}

std::vector<double> filter::filterFIR(const std::vector<double>& inputSignal)
{
	const size_t N = inputSignal.size();
	std::vector<double> outputSignal;
	outputSignal.reserve(N);

	for (int n = 0;n < N;n++)
	{
		double sum = 0;
		for (int k = 0;k < this->filterSize;k++)
		{
			if (n - k >= 0)
				sum += inputSignal[n-k] * filterSignal[k];
		}
		outputSignal.push_back(sum);
	}

	return outputSignal;
}