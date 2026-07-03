#include <cmath>
#include <vector>
#include <random>
#include "generator.h"
#include "../dsp/dsp.h"

generator::generator()
	: gen(std::random_device{}()),
	dist(0.0, 1.0),
	sampleRate(0),
	numSamples(0),
	noiseAmp(0)
{
}

void generator::setSampleRate(const double& sampleRate)
{
	this->sampleRate = sampleRate;
}

void generator::setNumSamples(const double& numSamples)
{
	this->numSamples = numSamples;
}

void generator::setNoiseAmp(const double& noiseAmp)
{
	this->noiseAmp = noiseAmp;
}

void generator::addSine(const Tone& tone)
{
	this->sines.push_back(tone);
}

void generator::addCosine(const Tone& tone)
{
	this->cosines.push_back(tone);
}

void generator::clearComponents()
{
	this->sampleRate = 0;
	this->numSamples = 0;
	this->noiseAmp = 0;
	this->cosines = std::vector<Tone>();
	this->sines = std::vector<Tone>();
}

std::vector<double> generator::generate()
{
	// x[n] = ∑sinusoids + noise[n]
	// don't add noise to each sinusoidal component, its an independant signal added after
	std::vector<double> signal;

	// with reserve you are not creating num samples double elements, unlike if you use the constructor
	// instead you are just allocating space for future pushback of elements
	signal.reserve(this->numSamples); 

	for (int i = 0;i < this->numSamples;i++)
	{
		double t = (double)i / this->sampleRate;

		double signal_value = 0;

		for (const Tone& tone : this->cosines)
			signal_value += tone.amp * std::cos(2 * PI * tone.freq * t);

		for (const Tone& tone : this->sines)
			signal_value += tone.amp * std::sin(2 * PI * tone.freq * t);

		double noise_value = dist(gen);
		signal_value += noise_value * this->noiseAmp;

		signal.push_back(signal_value);
	}

	return signal;
}