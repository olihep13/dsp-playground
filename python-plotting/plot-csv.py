import pandas as pd
import matplotlib.pyplot as plt

file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\amSignal.csv"  # change this to your file

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("DSP Signal")
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
plt.title("FFT Magnitude Spectrum")
plt.grid(True)
plt.show()