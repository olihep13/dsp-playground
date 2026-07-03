#pragma once

#include <vector>
#include "dsp.h"

class filter
{
public:
	filter(const double& sampleRate, const double& numSamples, const double& cutoffFrequency0, const bool& bandPass = false, const double& cutoffFrequency1 = 0);

	std::vector<double> filterFIR(const std::vector<double>& inputSignal);
	
	std::vector<double> filterSignal;
private:
	double sampleRate;
	double numSamples;
	double cutoffFrequency0;
	double cutoffFrequency1;
	double normalizedCutoffFrequency0;
	double normalizedCutoffFrequency1;
};