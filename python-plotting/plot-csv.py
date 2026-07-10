import pandas as pd
import matplotlib.pyplot as plt

r"""
# plot station B signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\filteredSignalTest.csv"  # change this to your file

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("filteredSignalTest")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

# plot station B signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\filterSignalTest.csv"  # change this to your file

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("filterSignalTest")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\amSignalFFT.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("amSignalFFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

"""

















# plot station B signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\timeDomainMessageSignalRadioStationB.csv"  # change this to your file

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("timeDomainMessageSignalRadioStationB Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of station B signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\messageSignalRadioStationBFFT.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("messageSignalRadioStationBFFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot am signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\amSignal.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("amSignal Time Domain")
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
plt.title("amSignalFFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\filteredAMSignalFFT.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("filteredAMSignalFFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of mixed bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\mixedFilteredAMSignalFFT.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("mixedFilteredAMSignalFFT Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of lowpass filter signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfFilterSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("fftOfFilterSignal Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of lowpass filtered mixed bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfFilteredMixedFilteredAMSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("fftOfFilteredMixedFilteredAMSignal Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot lowpass filtered mixed bandpass filtered am signal = should be identical to original message of station B
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\filteredMixedFilteredAMSignal.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("filteredMixedFilteredAMSignal Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()





















r"""
# tests with a single station
# plot station B signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\messageSignalRadioStationB.csv"  # change this to your file

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("messageSignalRadioStationB Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of station B signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfMessageStationB.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("fftOfMessageStationB Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot am signal
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\AMSignal.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("AMSignal Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfAMSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("fftOfAMSignal Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of mixed bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfMixedAMSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("fftOfMixedAMSignal Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of lowpass filter signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfFilterSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("fftOfFilterSignal Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot fft of lowpass filtered mixed bandpass filtered am signal
fileFFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\fftOfFilteredMixedAMSignal.csv"

df = pd.read_csv(fileFFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("fftOfFilteredMixedAMSignal Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

# plot lowpass filtered mixed bandpass filtered am signal = should be identical to original message of station B
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\filteredMixedAMSignal.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("filteredMixedAMSignal Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

# plot lowpass filtered mixed bandpass filtered am signal = should be identical to original message of station B
file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\originalMessage.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("originalMessage Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()
"""