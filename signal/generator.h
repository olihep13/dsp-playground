#pragma once

#include <vector>
#include "../dsp/dsp.h"
#include <random>

class generator
{
public:
	generator();

	void setSampleRate(const double& sampleRate);

	void setNumSamples(const double& numSamples);

	void setNoiseAmp(const double& noiseAmp);

	void addSine(const Tone& tone);

	void addCosine(const Tone& tone);

	void clearComponents();

	std::vector<double> generate();
private:
	std::mt19937 gen;
	std::normal_distribution<double> dist;
	double sampleRate;
	double numSamples;
	double noiseAmp;
	std::vector<Tone> cosines;
	std::vector<Tone> sines;

};