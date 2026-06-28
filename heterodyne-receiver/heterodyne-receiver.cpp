// heterodyne-receiver.cpp : Defines the entry point for the application.
//

#include "heterodyne-receiver.h"
#include "../signal/generator.h"

using namespace std;

void printSignal(const std::vector<double>& signal)
{
    for (size_t i = 0; i < signal.size(); i++)
    {
        std::cout << i << ": " << signal[i] << std::endl;
    }

    std::cout << "-------------------------------------\n";
}

int main()
{
    //==================================================
    // Test 1: Pure sine wave
    //==================================================

    std::cout << "Test 1: Sine Wave\n";

    generator gen1;

    gen1.setSampleRate(100);
    gen1.setNumSamples(20);

    gen1.addSine({ 1.0, 1.0 });

    auto signal1 = gen1.generate();

    printSignal(signal1);


    //==================================================
    // Test 2: Pure cosine wave
    //==================================================

    std::cout << "Test 2: Cosine Wave\n";

    generator gen2;

    gen2.setSampleRate(100);
    gen2.setNumSamples(20);

    gen2.addCosine({ 1.0, 1.0 });

    auto signal2 = gen2.generate();

    printSignal(signal2);


    //==================================================
    // Test 3: Sine + Cosine
    //==================================================

    std::cout << "Test 3: Sine + Cosine\n";

    generator gen3;

    gen3.setSampleRate(100);
    gen3.setNumSamples(20);

    gen3.addSine({ 2.0, 1.0 });
    gen3.addCosine({ 5.0, 0.5 });

    auto signal3 = gen3.generate();

    printSignal(signal3);


    //==================================================
    // Test 4: Noise only
    //==================================================

    std::cout << "Test 4: Noise\n";

    generator gen4;

    gen4.setSampleRate(100);
    gen4.setNumSamples(20);
    gen4.setNoiseAmp(0.2);

    auto signal4 = gen4.generate();

    printSignal(signal4);


    //==================================================
    // Test 5: Everything together
    //==================================================

    std::cout << "Test 5: Mixed Signal\n";

    generator gen5;

    gen5.setSampleRate(1000);
    gen5.setNumSamples(30);
    gen5.setNoiseAmp(0.1);

    gen5.addSine({ 10.0, 1.0 });
    gen5.addSine({ 40.0, 0.4 });
    gen5.addCosine({ 20.0, 0.7 });

    auto signal5 = gen5.generate();

    printSignal(signal5);

	return 0;
}
