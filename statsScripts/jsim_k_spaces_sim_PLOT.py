import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import pandas as pd

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# Initialize the plot
fig, ax = plt.subplots()

# Importing the spaces dataset
dt = pd.read_csv(path + '\\data\\jsim_yesSpaces_k_meanSim.csv')
# Plot the data
x = dt.iloc[:, 0]
y = dt.iloc[:, 1]
ax.plot(x, y, label='similarity (with spaces)', alpha=1.0)

# Importing the spaces dataset
dt = pd.read_csv(path + '\\data\\jsim_noSpaces_k_meanSim.csv')
# Plot the data
x = dt.iloc[:, 0]
y = dt.iloc[:, 1]
ax.plot(x, y, label='similarity (with NO spaces)', alpha=1.0)

# Add marker at average word size
ax.axvline(x=5.84, linestyle='--', linewidth=1, color='darkred', label='average word length (5.84)', alpha=0.75)

# Add legend
plt.legend(loc='upper right')

# Set "tick" frequency in x axis
step = 1.0
minRange = int(np.min(x))
maxRange = int(np.max(x))+1
plt.xticks([x * step for x in range(0, maxRange)])

# Set titles
ax.set(title="Mean Jaccard Similarity of 5 pairs", xlabel="shingle size (num chars)", ylabel="mean similarity (%)")

# Show the plot
# plt.show()

# Save the plot
plt.savefig(path + '\\plots\\jsim_spaces_k_sim.png', bbox_inches='tight')

# Clear and close the plot
plt.clf()
