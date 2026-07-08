import pandas as pd
import matplotlib.pyplot as plt

# plot station B signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\timeDomainMessageSignalRadioStationB.csv"  # change this to your file

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("DSP Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

# plot am signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\amSignal.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("DSP Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\amSignalFFT.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("FFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\filteredAMSignalFFT.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("FFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of mixed bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\mixedFilteredAMSignalFFT.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("FFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of lowpass filter signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfFilterSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("FFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of lowpass filtered mixed bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfFilteredMixedFilteredAMSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("FFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot lowpass filtered mixed bandpass filtered am signal = should be identical to original message of station B
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\filteredMixedFilteredAMSignal.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("DSP Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()