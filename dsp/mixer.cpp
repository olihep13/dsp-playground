#include <cmath>
#include <vector>
#include "mixer.h"
#include <format>
#include "dsp.h"

mixer::mixer(const double& sampleRate, const double& localOscillatorFrequency, const double& numSamples)
{
	this->sampleRate = sampleRate;
	this->numSamples = numSamples;
	this->localOscillatorFrequency = localOscillatorFrequency;

	for (int i = 0;i < this->numSamples;i++)
	{
		double t = (double)i / this->sampleRate;

		double signal_value = std::cos(2 * PI * this->localOscillatorFrequency * t);

		localOscillatorSignal.push_back(signal_value);
	}
}

std::vector<double> mixer::mix(const std::vector<double>& inputSignal)
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