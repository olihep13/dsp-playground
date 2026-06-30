#pragma once

#include <vector>
#include "dsp.h"

class mixer
{
public:
	mixer(const double& sampleRate, const double& localOscillatorFrequency, const double& numSamples);

	std::vector<double> mix(const std::vector<double>& inputSignal);
private:
	double sampleRate;
	double numSamples;
	double localOscillatorFrequency;
	std::vector<double> localOscillatorSignal;

};