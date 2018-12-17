# Import `pyplot` from `matplotlib`
# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import matplotlib.ticker as ticker
import pandas as pd
# from mpl_toolkits.mplot3d import Axes3D

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# Initialize the plot
fig = plt.figure()
ax = plt.axes()

# Importing the dataset
dt = pd.read_csv(path + '\\data\\signature_nHashFun_k_sim.csv', sep='\s*,\s*')

# Plot the data
kShingles = np.unique(dt.iloc[:, 1])
for k in kShingles:
    if (np.asscalar(k)%2 != 0):
        rows = dt.loc[dt.iloc[:, 1] == k]
        rows = rows.sort_values('NumberOfHashFunctions')
        x = rows.iloc[:, 0] # nHashFun
        y = rows.iloc[:, 2] # Similarity
        ax.plot(x,y, label='k = ' + str(np.asscalar(k)))
    
# Set "tick" frequency in x axis
maxRange = int(np.max(rows.iloc[:, 0]))+1
plt.xticks([x for x in range(0, maxRange, 50)])
# ax.xaxis.set_major_locator(ticker.MultipleLocator(base=0.5))

# ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='viridis', edgecolor='none', label='Signature Matrix Approximation', alpha=1.0)

# Add legend
plt.legend(loc='upper right')

# Set titles
ax.set(title="Signature Matrix Approximation for different Shingle sizes (k)", xlabel="number of hash functions", ylabel="similarity (%)")

# Show the plot

plt.show()

# Save the plot
# plt.savefig('plot')

# Clear and close the plot
# plt.clf()