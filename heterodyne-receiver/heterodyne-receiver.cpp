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
    // frequency resolution = Fs (sample/sec) / N (number of samples) = Hz amount per bin
    constexpr int numSamples = 1000;
    constexpr int sampleRate = 100;

    //==================================================
    // GENERATE MESSAGE SIGNALS
    //==================================================

    // MESSAGE FROM STATION A
    generator radioStationA;
    // so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    radioStationA.setSampleRate(sampleRate);
    radioStationA.setNumSamples(numSamples);
    // tone = .5 Hz, 1 Amplitude
    radioStationA.addCosine({ .5, 1 });
    auto messageSignalRadioStationA = radioStationA.generate();

    // MESSAGE FROM STATION B
    generator radioStationB;
    // so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    radioStationB.setSampleRate(sampleRate);
    radioStationB.setNumSamples(numSamples);
    // tone = 1 Hz, 1 Amplitude
    radioStationB.addCosine({ 1, 1 });
    auto messageSignalRadioStationB = radioStationB.generate();

    // MESSAGE FROM STATION C
    generator radioStationC;
    // so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    radioStationC.setSampleRate(sampleRate);
    radioStationC.setNumSamples(numSamples);
    // tone = .7 Hz, 1 Amplitude
    radioStationC.addCosine({ .7, 1 });
    auto messageSignalRadioStationC = radioStationC.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationA.csv", messageSignalRadioStationA, sampleRate);
    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationB.csv", messageSignalRadioStationB, sampleRate);
    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationC.csv", messageSignalRadioStationC, sampleRate);

    //==================================================
    // GENERATE AM SIGNAL MADE UP OF PREVIOUS MESSAGE SIGNALS
    //==================================================

    generator AMSignalGenerator;
    AMSignalGenerator.setSampleRate(sampleRate);
    AMSignalGenerator.setNumSamples(numSamples);
    // AM signal with carrier frequency at 9 Hz for message signal A
    AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationA, { 9, 1 }, .5);
    // AM signal with carrier frequency at 10 Hz for message signal B
    AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationB, { 10, 1 }, .5);
    // AM signal with carrier frequency at 13 Hz for message signal C
    AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationC, { 13, 1 }, .5);
    auto AMSignal = AMSignalGenerator.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\amSignal.csv", AMSignal, sampleRate);

    //==================================================
    // COMPUTE FFT OF AM SIGNAL (middle sample 50 is 0)
    //==================================================

    fft fastfft;

    auto fftOfAMSignal = fastfft.fft_float(AMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\amSignalFFT.csv", fftOfAMSignal, sampleRate);

    // note to ask chat:
    // I see the correct frequency domain graph, except I see it twice mirrored over the middle point, 0,
    // which in my case since im taking 100 samples is the point 50 in the graph.
    // So I see points at 58.5, 59, 59.5 for Station A; 59, 60, 61 for Station B; 62.3, 63, 63.7 for Station C
    // and then I see it mirrored over the 0 point at sample 50, so in the middle of my graph at 41.5, 41, etc.
    // is this normal since my signals are periodic? no right? Probably has to do with the discrete implementation in code?

    //==================================================
    // BANDPASS FILTER - keep Station B, reject Station A and C
    //==================================================

    filter filt1(sampleRate, numSamples, 8.5, true, 11.5);

    auto filteredAMSignal = filt1.filterFIR(AMSignal);

    auto fftOfFilteredAMSignal = fastfft.fft_float(filteredAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredAMSignalFFT.csv", fftOfFilteredAMSignal, sampleRate);
    // note to ask chat:
    // This may or may not be working, we see the left jump in the frquency domain graph at 59 (9 Hz) as larger than the other two
    // Is this because we had overlapping frequency domain spectrum there between station A and B?
    
    ////==================================================
    //// MIX SIGNALS - at carrier frequency for Station B (10 Hz)
    ////==================================================

    mixer mixObj(sampleRate, numSamples, 10); // 10 Hz carrier frequency at station B

    auto mixedFilteredAMSignal = mixObj.mix(filteredAMSignal);

    auto fftOfMixedFilteredAMSignal = fastfft.fft_float(mixedFilteredAMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\mixedFilteredAMSignalFFT.csv", fftOfMixedFilteredAMSignal, sampleRate);

    //==================================================
    // LOWPASS FILTER - remove sum and keep difference of mix
    //==================================================

    filter filt2(sampleRate, numSamples, 3);

    auto filterSignal = filt2.filterSignal;

    auto fftOfFilterSignal = fastfft.fft_float(filterSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilterSignal.csv", fftOfFilterSignal, sampleRate);

    auto filteredMixedFilteredAMSignal = filt2.filterFIR(mixedFilteredAMSignal);

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredMixedFilteredAMSignal.csv", filteredMixedFilteredAMSignal, sampleRate);

    auto fftOfFilteredMixedFilteredAMSignal = fastfft.fft_float(filteredMixedFilteredAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilteredMixedFilteredAMSignal.csv", fftOfFilteredMixedFilteredAMSignal, sampleRate);

    // note for chat:
    // I believe theres an error as at index 50, i.e. at 0 our filter is very low, close to 0 at 0.06
    // might not be a filter issue, we see a part of our signal preserved after low pass filter
    // maybe bandpass filter broken?

    return 0;
}
