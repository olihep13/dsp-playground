import pandas as pd
import matplotlib.pyplot as plt

file = r"C:\Users\OLIVI\work\dsp-playground\python-plotting\csv\signal5.csv"  # change this to your file

df = pd.read_csv(file)

plt.figure(figsize=(10, 5))
plt.plot(df["time"], df["amplitude"], label="signal")

plt.title("DSP Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)

plt.legend()
plt.show()