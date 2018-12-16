# Import `pyplot` from `matplotlib`
# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import pandas as pd
# from mpl_toolkits.mplot3d import Axes3D

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# Initialize the plot
fig, ax = plt.subplots()

# Importing the first dataset
dt = pd.read_csv(path + '\\data\\jsim_k_sim.csv')

# Plot the data
x = dt.iloc[:, :-1]
y = dt.iloc[:, -1:]
ax.plot(x, y, linewidth=3, label='Jaccard Similarity', alpha=0.75)

# Importing the second dataset
dt = pd.read_csv(path + '\\data\\signature_k_sim.csv')

# Plot the data
x = dt.iloc[:, :-1]
y = dt.iloc[:, -1:]
ax.plot(x, y, linewidth=3, label='Signature Matrix Approximation', alpha=0.75)

# Add legend
plt.legend(loc='upper right')

# Set "tick" frequency in x axis
step = 1.0
minRange = int(np.min(x))
maxRange = int(np.max(x))+1
plt.xticks([x * step for x in range(minRange, maxRange)])
# ax.xaxis.set_major_locator(ticker.MultipleLocator(base=0.5))

# Set titles
ax.set(title="Jaccard Similarity VS Signature Matrix Approximation", xlabel="shingle size (num chars)", ylabel="similarity (%)")

# Show the plot
plt.show()

# Save the plot
# plt.savefig('plot')

# Clear and close the plot
# plt.clf()