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

filter::filter(const double& sampleRate, const double& numSamples, const double& cutoffFrequency0, const bool& bandPass, const double& cutoffFrequency1)
{
	this->sampleRate = sampleRate;
	this->numSamples = numSamples;
	this->cutoffFrequency0 = cutoffFrequency0;
	this->cutoffFrequency1 = cutoffFrequency1;
	this->normalizedCutoffFrequency0 = this->cutoffFrequency0 / this->sampleRate;
	this->normalizedCutoffFrequency1 = this->cutoffFrequency1 / this->sampleRate;

	if (bandPass)
	{
		// BANDPASS
		for (int i = 0;i < this->numSamples;i++)
		{
			double index = i - (this->numSamples / 2);
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

			signal_value *= .5 - .5*std::cos((2*PI*i)/(this->numSamples-1)); //hann window

			filterSignal.push_back(signal_value);
		}
	}
	else
	{
		// LOWPASS
		for (int i = 0;i < this->numSamples;i++)
		{
			double index = i - (this->numSamples / 2);
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
			
			signal_value *= .5 - .5 * std::cos((2 * PI * i) / (this->numSamples - 1)); //hann window

			filterSignal.push_back(signal_value);
		}
	}
}

std::vector<double> filter::filterFIR(const std::vector<double>& inputSignal)
{
	// NOTE = my input vector and filter vector are assumed to be the same size
	if (inputSignal.size() != numSamples)
		throw std::runtime_error("Input signal has wrong length.");

	std::vector<double> outputSignal;
	outputSignal.reserve(this->numSamples);

	for (int n = 0;n < this->numSamples;n++)
	{
		double sum = 0;
		for (int k = 0;k < this->numSamples;k++)
		{
			if (n - k >= 0)
				sum += inputSignal[k] * filterSignal[n - k];
		}
		outputSignal.push_back(sum);
	}

	return outputSignal;
}