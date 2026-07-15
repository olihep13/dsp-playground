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

    for (int i = N / 2; i < N; i++)
        rotatedFFTOutput.push_back(fftOutput[i]);

    for (int i = 0; i < N / 2; i++)
        rotatedFFTOutput.push_back(fftOutput[i]);

    std::ofstream file(filename);

    file << "Frequency,Magnitude,Phase\n";

    for (int k = 0; k < N; k++)
    {
        double frequency = (k - N / 2) * sampleRate / N;

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
    constexpr int numSamples = 100000;
    constexpr int sampleRate = 1000;
    constexpr int filterSize = 1000;
    constexpr int modulationIndex = 1;

    // station message frequencies in Hz
    constexpr double stationAMessageFrequency = .5;
    constexpr double stationBMessageFrequency = 1;
    constexpr double stationCMessageFrequency = .7;

    // station carrier frequencies in Hz
    constexpr double stationACarrierFrequency = 30;
    constexpr double stationBCarrierFrequency = 50;
    constexpr double stationCCarrierFrequency = 70;

    constexpr double firstLocalOscillatorMixerFrequency = 30;
    constexpr double secondLocalOscillatorMixerFrequency = 20;

    //==================================================
    // GENERATE MESSAGE SIGNALS - 3 AM SIGNALS
    //==================================================

    // MESSAGE FROM STATION A
    generator radioStationA;
    radioStationA.setSampleRate(sampleRate);
    radioStationA.setNumSamples(numSamples);
    // tone = .5 Hz, 1 Amplitude
    radioStationA.addCosine({ stationAMessageFrequency, 1 });
    auto messageSignalRadioStationA = radioStationA.generate();

    // MESSAGE FROM STATION B
    generator radioStationB;
    radioStationB.setSampleRate(sampleRate);
    radioStationB.setNumSamples(numSamples);
    // tone = 1 Hz, 1 Amplitude
    radioStationB.addCosine({ stationBMessageFrequency, 1 });
    auto messageSignalRadioStationB = radioStationB.generate();

    // MESSAGE FROM STATION C
    generator radioStationC;
    radioStationC.setSampleRate(sampleRate);
    radioStationC.setNumSamples(numSamples);
    // tone = .7 Hz, 1 Amplitude
    radioStationC.addCosine({ stationCMessageFrequency, 1 });
    auto messageSignalRadioStationC = radioStationC.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationA.csv", messageSignalRadioStationA, sampleRate);
    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationB.csv", messageSignalRadioStationB, sampleRate);
    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationC.csv", messageSignalRadioStationC, sampleRate);

    fft fastfft;

    auto fftOfMessageStationB = fastfft.dft_float(messageSignalRadioStationB);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftMessageStationB.csv", fftOfMessageStationB, sampleRate);

    //==================================================
    // GENERATE AM SIGNAL MADE UP OF PREVIOUS MESSAGE SIGNALS
    //==================================================

    generator AMSignalGenerator;
    AMSignalGenerator.setSampleRate(sampleRate);
    AMSignalGenerator.setNumSamples(numSamples);
    // AM signal with carrier frequency at 9 Hz for message signal A
    AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationA, { stationACarrierFrequency, 1 }, modulationIndex);
    // AM signal with carrier frequency at 10 Hz for message signal B
    AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationB, { stationBCarrierFrequency, 1 }, modulationIndex);
    // AM signal with carrier frequency at 13 Hz for message signal C
    AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationC, { stationCCarrierFrequency, 1 }, modulationIndex);
    auto AMSignal = AMSignalGenerator.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\AMSignal.csv", AMSignal, sampleRate);

    //==================================================
    // COMPUTE DFT OF AM SIGNAL
    //==================================================

    auto fftOfAMSignal = fastfft.dft_float(AMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftAMSignal.csv", fftOfAMSignal, sampleRate);




    //==================================================
    // HOMODYNE RECEIVER
    //==================================================

    //==================================================
    // BANDPASS FILTER - keep Station B, reject Station A and C
    //==================================================

    filter filterHomodyne1(sampleRate, filterSize, stationBCarrierFrequency - stationBMessageFrequency * 2, true, stationBCarrierFrequency + stationBMessageFrequency * 2);

    auto filteredAMSignal = filterHomodyne1.filterFIR(AMSignal);

    auto dftFilteredAMSignal = fastfft.dft_float(filteredAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftFilteredAMSignalHomodyne.csv", dftFilteredAMSignal, sampleRate);

    //==================================================
    // MIX SIGNALS - at carrier frequency for Station B
    //==================================================

    mixer mixerHomodyne(sampleRate, numSamples, stationBCarrierFrequency);

    auto mixedFilteredAMSignal = mixerHomodyne.mix(filteredAMSignal);

    auto dftMixedFilteredAMSignal = fastfft.dft_float(mixedFilteredAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftMixedFilteredAMSignalHomodyne.csv", dftMixedFilteredAMSignal, sampleRate);

    //==================================================
    // LOWPASS FILTER - remove sum and keep difference of mix
    //==================================================

    filter filterHomodyne2(sampleRate, filterSize, 3);

    auto filteredMixedFilteredAMSignal = filterHomodyne2.filterFIR(mixedFilteredAMSignal);

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredMixedFilteredAMSignalHomodyne.csv", filteredMixedFilteredAMSignal, sampleRate);

    auto dftFilteredMixedFilteredAMSignal = fastfft.dft_float(filteredMixedFilteredAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftFilteredMixedFilteredAMSignalHomodyne.csv", dftFilteredMixedFilteredAMSignal, sampleRate);

    //==================================================
    // RECOVER MESSAGE - left with : (Ac / 2) * ​​(1 + u * m(t)) where u (modulation index) and Ac (carrier amplitude)
    //==================================================

    std::vector<double> originalMessageHomodyne;
    for (int i = 0;i < filteredMixedFilteredAMSignal.size();i++)
    {
        originalMessageHomodyne.push_back(((filteredMixedFilteredAMSignal[i] * 2) - 1) / modulationIndex);
    }

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\originalMessageHomodyne.csv", originalMessageHomodyne, sampleRate);



    
    //==================================================
    // HETERODYNE RECEIVER
    //==================================================
    
    ////==================================================
    //// MIX SIGNALS - mix with LO = 30 Hz
    ////==================================================

    mixer mixerHeterodyne1(sampleRate, numSamples, firstLocalOscillatorMixerFrequency);

    auto mixedAMSignal = mixerHeterodyne1.mix(AMSignal);

    auto dftMixedAMSignal = fastfft.dft_float(mixedAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftMixedAMSignalHeterodyne.csv", dftMixedAMSignal, sampleRate);

    //==================================================
    // BANDPASS FILTER - 18 - 22 Hz, intermediate frequency of 20 Hz
    //==================================================

    filter filterHeterodyne1(sampleRate, filterSize, 18, true, 22);

    auto filteredMixedAMSignal = filterHeterodyne1.filterFIR(mixedAMSignal);

    auto dftFilteredMixedAMSignal = fastfft.dft_float(filteredMixedAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftFilteredMixedAMSignalHeterodyne.csv", dftFilteredMixedAMSignal, sampleRate);
    
    ////==================================================
    //// MIX SIGNALS - then mix again at another local oscillator LO = 20 Hz
    ////==================================================

    mixer mixerHeterodyne2(sampleRate, numSamples, secondLocalOscillatorMixerFrequency);

    auto mixedFilteredMixedAMSignal = mixerHeterodyne2.mix(filteredMixedAMSignal);

    auto dftMixedFilteredMixedAMSignal = fastfft.dft_float(mixedFilteredMixedAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftMixedFilteredMixedAMSignalHeterodyne.csv", dftMixedFilteredMixedAMSignal, sampleRate);

    //==================================================
    // LOWPASS FILTER - remove sum and keep difference of mix, finall Lowpass filter: 0 - 3 Hz
    //==================================================

    filter filterHeterodyne2(sampleRate, filterSize, 3);

    auto filteredMixedFilteredMixedAMSignal = filterHeterodyne2.filterFIR(mixedFilteredMixedAMSignal);

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredMixedFilteredMixedAMSignalHeterodyne.csv", filteredMixedFilteredMixedAMSignal, sampleRate);

    auto dftFilteredMixedFilteredMixedAMSignal = fastfft.dft_float(filteredMixedFilteredMixedAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\dftFilteredMixedFilteredMixedAMSignalHeterodyne.csv", dftFilteredMixedFilteredMixedAMSignal, sampleRate);
    
    //==================================================
    // RECOVER MESSAGE - left with : (Ac / 4) * ​​(1 + u * m(t)) where u (modulation index) and Ac (carrier amplitude)
    //==================================================

    std::vector<double> originalMessageHeterodyne;
    for (int i = 0;i < filteredMixedFilteredMixedAMSignal.size();i++)
    {
        originalMessageHeterodyne.push_back(((filteredMixedFilteredMixedAMSignal[i] * 4) - 1) / modulationIndex);
    }

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\originalMessageHeterodyne.csv", originalMessageHeterodyne, sampleRate);

    return 0;
}
