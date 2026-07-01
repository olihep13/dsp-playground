#pragma once

#include <vector>
#include "dsp.h"

class filter
{
public:
	filter(const double& sampleRate, const double& numSamples, const double& cutoffFrequency0, const bool& bandPass, const double& cutoffFrequency1 = 0);

	std::vector<double> filterFIR(const std::vector<double>& inputSignal);
private:
	double sampleRate;
	double numSamples;
	double cutoffFrequency0;
	double cutoffFrequency1;
	double normalizedCutoffFrequency0;
	double normalizedCutoffFrequency1;
	std::vector<double> filterSignal;
};