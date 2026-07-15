import pandas as pd
import matplotlib.pyplot as plt

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

# plot dft of station B signal
fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftMessageStationB.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftMessageStationB Magnitude Spectrum")
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

# plot dft of am signal
fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftAMSignal.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftAMSignal Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

##########################
# 3 AM STATIONS HOMODYNE
##########################

fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftFilteredAMSignalHomodyne.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftFilteredAMSignalHomodyne Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftMixedFilteredAMSignalHomodyne.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftMixedFilteredAMSignalHomodyne Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftFilteredMixedFilteredAMSignalHomodyne.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftFilteredMixedFilteredAMSignalHomodyne Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\originalMessageHomodyne.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("originalMessageHomodyne Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()

##########################
# 3 AM STATIONS HETERODYNE
##########################

fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftMixedAMSignalHeterodyne.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftMixedAMSignalHeterodyne Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftFilteredMixedAMSignalHeterodyne.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftFilteredMixedAMSignalHeterodyne Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftMixedFilteredMixedAMSignalHeterodyne.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftMixedFilteredMixedAMSignalHeterodyne Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

fileDFT = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\dftFilteredMixedFilteredMixedAMSignalHeterodyne.csv"

df = pd.read_csv(fileDFT)

plt.plot(df["Frequency"], df["Magnitude"])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("dftFilteredMixedFilteredMixedAMSignalHeterodyne Magnitude Spectrum")
plt.grid(True)
plt.legend()
plt.show()

file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\originalMessageHeterodyne.csv"

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("originalMessageHeterodyne Time Domain")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.show()