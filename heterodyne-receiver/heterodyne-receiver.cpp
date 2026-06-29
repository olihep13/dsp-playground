#include "heterodyne-receiver.h"
#include "../signal/generator.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void writeCSV(const std::string& filename, const std::vector<double>& signal, double sampleRate)
{
    std::ofstream file(filename);

    file << "index,time,amplitude\n";

    for (size_t i = 0; i < signal.size(); i++)
    {
        double t = static_cast<double>(i) / sampleRate;
        file << i << "," << t << "," << signal[i] << "\n";
    }
}

int main()
{
    //==================================================
    // Test 1: Pure sine wave
    //==================================================

    std::cout << "Test 1: Sine Wave\n";

    generator gen1;

    gen1.setSampleRate(1000);
    gen1.setNumSamples(1000);

    gen1.addSine({ 1.0, 1.0 });

    auto signal1 = gen1.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\signal1.csv", signal1, 100);

    //==================================================
    // Test 2: Pure cosine wave
    //==================================================

    std::cout << "Test 2: Cosine Wave\n";

    generator gen2;

    gen2.setSampleRate(1000);
    gen2.setNumSamples(1000);

    gen2.addCosine({ 1.0, 1.0 });

    auto signal2 = gen2.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\signal2.csv", signal2, 100);

    //==================================================
    // Test 3: Sine + Cosine
    //==================================================

    std::cout << "Test 3: Sine + Cosine\n";

    generator gen3;

    gen3.setSampleRate(1000);
    gen3.setNumSamples(1000);

    gen3.addSine({ 2.0, 1.0 });
    gen3.addCosine({ 5.0, 0.5 });

    auto signal3 = gen3.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\signal3.csv", signal3, 100);


    //==================================================
    // Test 4: Noise only
    //==================================================

    std::cout << "Test 4: Noise\n";

    generator gen4;

    gen4.setSampleRate(1000);
    gen4.setNumSamples(1000);
    gen4.setNoiseAmp(0.2);

    auto signal4 = gen4.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\signal4.csv", signal4, 100);


    //==================================================
    // Test 5: Everything together
    //==================================================

    std::cout << "Test 5: Mixed Signal\n";

    generator gen5;

    gen5.setSampleRate(1000);
    gen5.setNumSamples(1000);
    gen5.setNoiseAmp(0.1);

    gen5.addSine({ 10.0, 1.0 });
    gen5.addSine({ 40.0, 0.4 });
    gen5.addCosine({ 20.0, 0.7 });

    auto signal5 = gen5.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\signal5.csv", signal5, 1000);

    return 0;
}
