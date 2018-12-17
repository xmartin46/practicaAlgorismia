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


# Importing the dataset
dt = pd.read_csv(path + '\\data\\jsim_meanTime.csv')
# Plot the data
x = dt.iloc[:, 0]
y = dt.iloc[:, 1]
ax.plot(x, y, alpha=1.0)

# Add marker at average word size
# ax.axvline(x=5.84, linestyle='--', linewidth=1, color='darkred', label='average word length (5.84)', alpha=0.75)

# Add legend
plt.legend(loc='upper right')

# Set "tick" frequency in x axis
step = 1.0
minRange = int(np.min(x))
maxRange = int(np.max(x))+1
plt.xticks([x * step for x in range(0, maxRange)])

# Set "tick" frequency in y axis
plt.yticks([x for x in range(0, 20)])

# Set titles
ax.set(title="Average (of 5) Time to compute Jaccard Similarity", xlabel="shingle size (num chars)", ylabel="mean time of 5 pairs of docs (ms)")

# Show the plot
# plt.show()

# Save the plot
plt.savefig(path + '\\plots\\jsim_k_meanTime.png', bbox_inches='tight')

# Clear and close the plot
plt.clf()
