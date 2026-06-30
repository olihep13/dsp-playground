#include <cmath>
#include <vector>
#include "filter.h"
#include <format>
#include "dsp.h"

filter::filter(const double& sampleRate, const double& numSamples, const double& cutoffFrequency0, const bool& bandPass, const double& cutoffFrequency1 = 0)
{
	this->sampleRate = sampleRate;
	this->numSamples = numSamples;
	this->cutoffFrequency0 = cutoffFrequency0;
	this->cutoffFrequency1 = cutoffFrequency1;

	if (bandPass)
	{
		for (int i = 0;i < this->numSamples;i++)
		{
			double t = (double)i / this->sampleRate;

			double signal_value = std::cos(2 * PI * this->localOscillatorFrequency * t);

			filterSignal.push_back(signal_value);
		}
	}
	else
	{
		for (int i = 0;i < this->numSamples;i++)
		{
			double t = (double)i / this->sampleRate;

			double signal_value = std::sin(2 * PI * this->cutoffFrequency0 * i) / (PI * i);

			filterSignal.push_back(signal_value);
		}
	}
}

std::vector<double> filter::filterFIR(const std::vector<double>& inputSignal)
{
	if (inputSignal.size() != numSamples)
		throw std::runtime_error("Input signal has wrong length.");

	std::vector<double> outputSignal;
	outputSignal.reserve(this->numSamples);

	for (int i = 0;i < this->numSamples;i++)
	{

		double signal_value = inputSignal[i] * localOscillatorSignal[i];

		outputSignal.push_back(signal_value);
	}

	return outputSignal;
}