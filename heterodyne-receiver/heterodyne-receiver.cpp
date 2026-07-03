#include "heterodyne-receiver.h"
#include "../signal/generator.h"
#include "../dsp/filter.h"
#include "../dsp/fft.h"
#include "../dsp/mixer.h"
#include <fstream>
#include <vector>
#include <string>
#include <complex>

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

void writeFFTCSV(
    const std::string& filename,
    const std::vector<std::complex<double>>& fftOutput,
    double sampleRate)
{
    int N = fftOutput.size();

    // our current fft output vector formatted as: 0 ... Fs/2 -Fs/2 ... 0
    // fix by rotating the elements as below:
    std::vector<std::complex<double>> rotatedFFTOutput;
    for (int i = N/2;i < N;i++)
    {
        rotatedFFTOutput.push_back(fftOutput[i]);
    }
    for (int i = 0;i < N/2 +1;i++)
    {
        rotatedFFTOutput.push_back(fftOutput[i]);
    }
    std::ofstream file(filename);

    file << "Frequency,Magnitude,Phase\n";

    for (int k = 0; k < N; k++)
    {
        double frequency = (double)k * sampleRate / N;

        double magnitude = std::abs(rotatedFFTOutput[k]);
        double phase = std::arg(rotatedFFTOutput[k]);

        file << frequency << ","
            << magnitude << ","
            << phase << "\n";
    }

    file.close();
}

int main()
{
    //==================================================
    // Test: Sinc function fft
    //==================================================

    // frequency resolution = Fs (sample/sec) / N (number of samples) = Hz amount per bin

    std::cout << "Test: Sinc function fft\n";

    generator genMessage;
    generator genSinusoidalCarrier;

    // so above, frequency resolution = 10000 (sample/sec) / 10000 (number of samples) = 1 Hz per bin
    genMessage.setSampleRate(10000);
    genMessage.setNumSamples(10000);
    genSinusoidalCarrier.setSampleRate(10000);
    genSinusoidalCarrier.setNumSamples(10000);

    // message
    genMessage.addCosine({ 1, 1 }); // 1 Hz, A=1
    auto messageSignal = genMessage.generate();

    // sinusoidal carrier, with carrier frequency at 10 Hz
    genSinusoidalCarrier.addCosine({ 10, 1 }); // 10Hz == 10 bins in the graph, A=1
    auto sinusoidalCarrierSignal = genSinusoidalCarrier.generate();

    std::vector<double> modulatedSignal;
    // multiply our signals
    for (int i = 0;i < 10000;i++)
    {
        modulatedSignal.push_back(1+messageSignal[i]*sinusoidalCarrierSignal[i]); // amplitude modulated signal
    }

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\amSignal.csv", modulatedSignal, 10000);

    fft fastfft;

    auto fftOfFilter = fastfft.fft_float(modulatedSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\amSignalFFT.csv", fftOfFilter, 10000);

    mixer mixObj(10000, 2, 10000);

    auto mixedSignal = mixObj.mix(modulatedSignal);

    auto fftOfMixedSignal = fastfft.fft_float(mixedSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\mixedSignalFFT.csv", fftOfMixedSignal, 10000);

    // filter fft, unrelated

    //filter filt(1000, 1000, 40);
    //
    //fftOfFilter = fastfft.fft_float(filt.filterSignal);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilter.csv", fftOfFilter, 1000);

    return 0;
}
