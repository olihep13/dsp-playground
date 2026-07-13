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
    // frequency resolution = Fs (sample/sec) / N (number of samples) = .1 Hz amount per bin
    constexpr int numSamples = 100000;
    constexpr int sampleRate = 1000;
    constexpr int filterSize = 1001;
    constexpr int modulationIndex = 1;

    // station message frequencies in Hz
    constexpr double stationAMessageFrequency = .5;
    constexpr double stationBMessageFrequency = 1;
    constexpr double stationCMessageFrequency = .7;

    // station carrier frequencies in Hz
    constexpr double stationACarrierFrequency = 30;
    constexpr double stationBCarrierFrequency = 50;
    constexpr double stationCCarrierFrequency = 70;

    constexpr double intermediateFrequency = 20;
    constexpr double firstLocalOscillatorMixerFrequency = 30; // ∣fc​−fLO​∣=fIF​ and fc=50, fIF=10
    constexpr double secondLocalOscillatorMixerFrequency = 30; // ∣fc​−fLO​∣=fIF​ and fc=50, fIF=10

    /*
    * FILTER TESTING 
    generator testSignal;
    testSignal.setSampleRate(sampleRate);
    testSignal.setNumSamples(numSamples);
    testSignal.addCosine({100,1});
    auto x = testSignal.generate();
    
    filter filtTest(sampleRate, filterSize, stationBMessageFrequency);

    auto filteredTest = filtTest.filterFIR(x);

    double maxError = 0;

    for (int i = 0; i < filterSize; i++)
    {
        maxError = std::max(
            maxError,
            std::abs(filteredTest[i] - filtTest.filterSignal[i]));
    }

    double rms = 0;
    for (double l : x)
        rms += l * l;
    rms = std::sqrt(rms / x.size());
    std::cout << "rms original signal: " << rms << std::endl;

    rms = 0;
    for (double l : filteredTest)
        rms += l * l;
    rms = std::sqrt(rms / filteredTest.size());
    std::cout << "rms filtered signal: " << rms << std::endl;

    std::cout << "error: " << maxError << std::endl;

    double mean = 0;
    for (double x : filteredTest)
        mean += x;
    mean /= filteredTest.size();
    std::cout << "mean:" << mean << std::endl;

    std::cout
        << filteredTest[5000]
        << std::endl;

        for (int i = 5000;i < 5015;i++)
            std::cout << filteredTest[i] << std::endl;

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredSignalTest.csv", filteredTest, sampleRate);
    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filterSignalTest.csv", x, sampleRate);

    fft fastfft;
    auto fftOfMessageStationB = fastfft.dft_float(filteredTest);
    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\amSignalFFT.csv", fftOfMessageStationB, sampleRate);
    */
    
















    
    ////==================================================
    //// GENERATE MESSAGE SIGNALS ---------------- 3 AM SIGNALS
    ////==================================================

    //// MESSAGE FROM STATION A
    //generator radioStationA;
    //// so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    //radioStationA.setSampleRate(sampleRate);
    //radioStationA.setNumSamples(numSamples);
    //// tone = .5 Hz, 1 Amplitude
    //radioStationA.addCosine({ stationAMessageFrequency, 1 });
    //auto messageSignalRadioStationA = radioStationA.generate();

    //// MESSAGE FROM STATION B
    //generator radioStationB;
    //// so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    //radioStationB.setSampleRate(sampleRate);
    //radioStationB.setNumSamples(numSamples);
    //// tone = 1 Hz, 1 Amplitude
    //radioStationB.addCosine({ stationBMessageFrequency, 1 });
    //auto messageSignalRadioStationB = radioStationB.generate();

    //// MESSAGE FROM STATION C
    //generator radioStationC;
    //// so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    //radioStationC.setSampleRate(sampleRate);
    //radioStationC.setNumSamples(numSamples);
    //// tone = .7 Hz, 1 Amplitude
    //radioStationC.addCosine({ stationCMessageFrequency, 1 });
    //auto messageSignalRadioStationC = radioStationC.generate();

    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationA.csv", messageSignalRadioStationA, sampleRate);
    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationB.csv", messageSignalRadioStationB, sampleRate);
    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationC.csv", messageSignalRadioStationC, sampleRate);

    //fft fastfft;

    //auto fftOfMessageStationB = fastfft.dft_float(messageSignalRadioStationB);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\messageSignalRadioStationBFFT.csv", fftOfMessageStationB, sampleRate);

    ////==================================================
    //// GENERATE AM SIGNAL MADE UP OF PREVIOUS MESSAGE SIGNALS
    ////==================================================

    //generator AMSignalGenerator;
    //AMSignalGenerator.setSampleRate(sampleRate);
    //AMSignalGenerator.setNumSamples(numSamples);
    //// AM signal with carrier frequency at 9 Hz for message signal A
    //AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationA, { stationACarrierFrequency, 1 }, modulationIndex);
    //// AM signal with carrier frequency at 10 Hz for message signal B
    //AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationB, { stationBCarrierFrequency, 1 }, modulationIndex);
    //// AM signal with carrier frequency at 13 Hz for message signal C
    //AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationC, { stationCCarrierFrequency, 1 }, modulationIndex);
    //auto AMSignal = AMSignalGenerator.generate();

    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\amSignal.csv", AMSignal, sampleRate);

    ////==================================================
    //// COMPUTE FFT OF AM SIGNAL (middle sample 50 is 0)
    ////==================================================

    //auto fftOfAMSignal = fastfft.dft_float(AMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\amSignalFFT.csv", fftOfAMSignal, sampleRate);

    //// note to ask chat:
    //// I see the correct frequency domain graph, except I see it twice mirrored over the middle point, 0,
    //// which in my case since im taking 100 samples is the point 50 in the graph.
    //// So I see points at 58.5, 59, 59.5 for Station A; 59, 60, 61 for Station B; 62.3, 63, 63.7 for Station C
    //// and then I see it mirrored over the 0 point at sample 50, so in the middle of my graph at 41.5, 41, etc.
    //// is this normal since my signals are periodic? no right? Probably has to do with the discrete implementation in code?

    ////==================================================
    //// BANDPASS FILTER - keep Station B, reject Station A and C
    ////==================================================

    //filter filt1(sampleRate, filterSize, stationBCarrierFrequency - stationBMessageFrequency * 2, true, stationBCarrierFrequency + stationBMessageFrequency * 2);

    //auto filteredAMSignal = filt1.filterFIR(AMSignal);

    //auto fftOfFilteredAMSignal = fastfft.dft_float(filteredAMSignal);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredAMSignalFFT.csv", fftOfFilteredAMSignal, sampleRate);
    //// note to ask chat:
    //// This may or may not be working, we see the left jump in the frquency domain graph at 59 (9 Hz) as larger than the other two
    //// Is this because we had overlapping frequency domain spectrum there between station A and B?
    //
    //////==================================================
    ////// MIX SIGNALS - at carrier frequency for Station B
    //////==================================================

    //mixer mixObj(sampleRate, numSamples, stationBCarrierFrequency); // 10 Hz carrier frequency at station B

    //auto mixedFilteredAMSignal = mixObj.mix(filteredAMSignal);

    //auto fftOfMixedFilteredAMSignal = fastfft.dft_float(mixedFilteredAMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\mixedFilteredAMSignalFFT.csv", fftOfMixedFilteredAMSignal, sampleRate);

    ////==================================================
    //// LOWPASS FILTER - remove sum and keep difference of mix
    ////==================================================

    //filter filt2(sampleRate, filterSize, 3);

    //auto filterSignal = filt2.filterSignal;

    //auto fftOfFilterSignal = fastfft.dft_float(filterSignal);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilterSignal.csv", fftOfFilterSignal, sampleRate);

    //auto filteredMixedFilteredAMSignal = filt2.filterFIR(mixedFilteredAMSignal);

    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredMixedFilteredAMSignal.csv", filteredMixedFilteredAMSignal, sampleRate);

    //auto fftOfFilteredMixedFilteredAMSignal = fastfft.dft_float(filteredMixedFilteredAMSignal);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilteredMixedFilteredAMSignal.csv", fftOfFilteredMixedFilteredAMSignal, sampleRate);

    // note for chat:
    // I believe theres an error as at index 50, i.e. at 0 our filter is very low, close to 0 at 0.06
    // might not be a filter issue, we see a part of our signal preserved after low pass filter
    // maybe bandpass filter broken

    
    

















    
    //==================================================
    // GENERATE MESSAGE SIGNALS ---------------- SIGNAL AM SIGNAL
    //==================================================

    // MESSAGE FROM STATION B
    generator radioStationB;
    // so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    radioStationB.setSampleRate(sampleRate);
    radioStationB.setNumSamples(numSamples);
    // tone = 1 Hz, 1 Amplitude
    radioStationB.addCosine({ stationBMessageFrequency, 1 });
    auto messageSignalRadioStationB = radioStationB.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\messageSignalRadioStationBSingle.csv", messageSignalRadioStationB, sampleRate);

    fft fastfft;

    auto fftOfMessageStationB = fastfft.dft_float(messageSignalRadioStationB);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfMessageStationBSingle.csv", fftOfMessageStationB, sampleRate);

    //==================================================
    // GENERATE AM SIGNAL MADE UP OF PREVIOUS MESSAGE SIGNALS
    //==================================================

    generator AMSignalGenerator;
    AMSignalGenerator.setSampleRate(sampleRate);
    AMSignalGenerator.setNumSamples(numSamples);
    // AM signal with carrier frequency at 10 Hz for message signal B
    AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationB, { stationBCarrierFrequency, 1 }, modulationIndex);
    auto AMSignal = AMSignalGenerator.generate();

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\AMSignalSingle.csv", AMSignal, sampleRate);

    //==================================================
    // COMPUTE FFT OF AM SIGNAL (middle sample 50 is 0)
    //==================================================

    auto fftOfAMSignal = fastfft.dft_float(AMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfAMSignalSingle.csv", fftOfAMSignal, sampleRate);

    ////==================================================
    //// MIX SIGNALS - at carrier frequency for Station B
    ////==================================================

    mixer mixObj(sampleRate, numSamples, stationBCarrierFrequency); // 10 Hz carrier frequency at station B

    auto mixedAMSignal = mixObj.mix(AMSignal);

    auto fftOfMixedAMSignal = fastfft.dft_float(mixedAMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfMixedAMSignalSingle.csv", fftOfMixedAMSignal, sampleRate);

    //==================================================
    // LOWPASS FILTER - remove sum and keep difference of mix
    //==================================================

    filter filt2(sampleRate, filterSize, 3);

    auto filterSignal = filt2.filterSignal;

    auto fftOfFilterSignal = fastfft.dft_float(filterSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilterSignalSingle.csv", fftOfFilterSignal, sampleRate);

    auto filteredMixedAMSignal = filt2.filterFIR(mixedAMSignal);

    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredMixedAMSignalSingle.csv", filteredMixedAMSignal, sampleRate);

    auto fftOfFilteredMixedAMSignal = fastfft.dft_float(filteredMixedAMSignal);

    writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilteredMixedAMSignalSingle.csv", fftOfFilteredMixedAMSignal, sampleRate);


    // left with envelope: (Ac/2)*​​(1+u*m(t)) where u = 0.5 (modulation index) and Ac = 1 (carrier amplitude)

    std::vector<double> originalMessage;
    for (int i = 0;i < filteredMixedAMSignal.size();i++)
    {
        originalMessage.push_back(((filteredMixedAMSignal[i] * 2) - 1) / modulationIndex);
    }


    writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\originalMessage.csv", originalMessage, sampleRate);

    













    //// receive am signals 
    //// mix with LO = 40 Hz
    //// The spectrum becomes: 0 Hz, 20 Hz, 40 Hz instead of 30 Hz, 50 Hz, 70 Hz
    //// Instead of your current bandpass: 48 - 52 Hz you would filter with bandpass: 18 - 22 Hz
    //// then mix again at another local oscillator LO = 20 Hz
    //// finall Lowpass filter: 0 - 3 Hz
    //
    ////==================================================
    //// GENERATE MESSAGE SIGNALS ---------------- 3 AM SIGNALS WITH IF
    ////==================================================

    //// MESSAGE FROM STATION A
    //generator radioStationA;
    //// so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    //radioStationA.setSampleRate(sampleRate);
    //radioStationA.setNumSamples(numSamples);
    //// tone = .5 Hz, 1 Amplitude
    //radioStationA.addCosine({ stationAMessageFrequency, 1 });
    //auto messageSignalRadioStationA = radioStationA.generate();

    //// MESSAGE FROM STATION B
    //generator radioStationB;
    //// so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    //radioStationB.setSampleRate(sampleRate);
    //radioStationB.setNumSamples(numSamples);
    //// tone = 1 Hz, 1 Amplitude
    //radioStationB.addCosine({ stationBMessageFrequency, 1 });
    //auto messageSignalRadioStationB = radioStationB.generate();

    //// MESSAGE FROM STATION C
    //generator radioStationC;
    //// so above, frequency resolution = sample rate 100 (sample/sec) / 1000 (number of samples) = .1 Hz per bin
    //radioStationC.setSampleRate(sampleRate);
    //radioStationC.setNumSamples(numSamples);
    //// tone = .7 Hz, 1 Amplitude
    //radioStationC.addCosine({ stationCMessageFrequency, 1 });
    //auto messageSignalRadioStationC = radioStationC.generate();

    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationA.csv", messageSignalRadioStationA, sampleRate);
    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationB.csv", messageSignalRadioStationB, sampleRate);
    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\timeDomainMessageSignalRadioStationC.csv", messageSignalRadioStationC, sampleRate);

    //fft fastfft;

    //auto fftOfMessageStationB = fastfft.dft_float(messageSignalRadioStationB);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfMessageStationB.csv", fftOfMessageStationB, sampleRate);

    ////==================================================
    //// GENERATE AM SIGNAL MADE UP OF PREVIOUS MESSAGE SIGNALS
    ////==================================================

    //generator AMSignalGenerator;
    //AMSignalGenerator.setSampleRate(sampleRate);
    //AMSignalGenerator.setNumSamples(numSamples);
    //// AM signal with carrier frequency at 9 Hz for message signal A
    //AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationA, { stationACarrierFrequency, 1 }, modulationIndex);
    //// AM signal with carrier frequency at 10 Hz for message signal B
    //AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationB, { stationBCarrierFrequency, 1 }, modulationIndex);
    //// AM signal with carrier frequency at 13 Hz for message signal C
    //AMSignalGenerator.addAMSignalCosine(messageSignalRadioStationC, { stationCCarrierFrequency, 1 }, modulationIndex);
    //auto AMSignal = AMSignalGenerator.generate();

    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\AMSignal.csv", AMSignal, sampleRate);

    ////==================================================
    //// COMPUTE FFT OF AM SIGNAL (middle sample 50 is 0)
    ////==================================================

    //auto fftOfAMSignal = fastfft.dft_float(AMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfAMSignal.csv", fftOfAMSignal, sampleRate);

    //////==================================================
    ////// MIX SIGNALS - mix with LO = 30 Hz
    ////// The spectrum becomes: 0 Hz, 20 Hz, 40 Hz instead of 30 Hz, 50 Hz, 70 Hz
    //////==================================================

    //mixer mixObj(sampleRate, numSamples, 30);

    //auto mixedAMSignal = mixObj.mix(AMSignal);

    //auto fftOfMixedAMSignal = fastfft.dft_float(mixedAMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    //// note: first mix does not work as expected. the incoming AM signal has a correct/expected fft.
    //// However, the output of the mix has a weird fft. we see a jump at 10 Hz, 30 Hz, 70 Hz, 90 Hz, and 110 Hz

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfMixedAMSignal.csv", fftOfMixedAMSignal, sampleRate);

    ////==================================================
    //// BANDPASS FILTER - Instead of your current bandpass: 48 - 52 Hz you would filter with bandpass: 18 - 22 Hz
    ////==================================================

    //filter filt1(sampleRate, filterSize, 18, true, 22);

    //auto filteredMixedAMSignal = filt1.filterFIR(mixedAMSignal);

    //auto fftOfFilteredMixedAMSignal = fastfft.dft_float(filteredMixedAMSignal);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilteredMixedAMSignal.csv", fftOfFilteredMixedAMSignal, sampleRate);
    //
    //////==================================================
    ////// MIX SIGNALS - then mix again at another local oscillator LO = 20 Hz
    //////==================================================

    //mixer mixObj2(sampleRate, numSamples, 20);

    //auto mixedFilteredMixedAMSignal = mixObj2.mix(filteredMixedAMSignal);

    //auto fftOfMixedFilteredMixedAMSignal = fastfft.dft_float(mixedFilteredMixedAMSignal); // output vector shows: 0 ... Fs/2 -Fs/2 ... 0

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfMixedFilteredMixedAMSignal.csv", fftOfMixedFilteredMixedAMSignal, sampleRate);

    ////==================================================
    //// LOWPASS FILTER - remove sum and keep difference of mix, finall Lowpass filter: 0 - 3 Hz
    ////==================================================

    //filter filt2(sampleRate, filterSize, 3);

    //auto filteredMixedFilteredMixedAMSignal = filt2.filterFIR(mixedFilteredMixedAMSignal);

    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\filteredMixedFilteredMixedAMSignal.csv", filteredMixedFilteredMixedAMSignal, sampleRate);

    //auto fftOfFilteredMixedFilteredMixedAMSignal = fastfft.dft_float(filteredMixedFilteredMixedAMSignal);

    //writeFFTCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\fftOfFilteredMixedFilteredMixedAMSignal.csv", fftOfFilteredMixedFilteredMixedAMSignal, sampleRate);
    //
    //// left with envelope : (Ac / 2) * ​​(1 + u * m(t)) where u = 0.5 (modulation index) and Ac = 1 (carrier amplitude)

    //std::vector<double> originalMessage;
    //for (int i = 0;i < filteredMixedFilteredMixedAMSignal.size();i++)
    //{
    //    originalMessage.push_back(((filteredMixedFilteredMixedAMSignal[i] * 2) - 1) / modulationIndex);
    //}

    //writeCSV("C:\\Users\\OLIVI\\work\\dsp-playground\\python-plotting\\csv\\originalMessage.csv", originalMessage, sampleRate);

    return 0;
}
