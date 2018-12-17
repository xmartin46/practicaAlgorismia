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
dt = pd.read_csv(path + '\\data\\sig_time_modular_vs_jenkinsFunc.csv', sep='\s*,\s*')

# Plot the data
hashFun = np.unique(dt.iloc[:, 0])
for n in hashFun[:]:
    rows = dt.loc[dt.iloc[:, 0] == n]
    rows = rows.sort_values('k')
    x = rows.iloc[:, 1] # kShingles
    y = rows.iloc[:, 2] # Similarity
    ax.plot(x,y, label='nHashes = ' + str(np.asscalar(n)))
    
# Set "tick" frequency in x axis
maxRange = int(np.max(rows.iloc[:, 1]))+1
plt.xticks([x for x in range(0, maxRange, 1)])
# ax.xaxis.set_major_locator(ticker.MultipleLocator(base=0.5))

# Add legend
plt.legend(loc='upper right')

# Move legend so that it doesn't block the plot
ax.legend(bbox_to_anchor=(1, 1))

# Set titles
ax.set(title="(time from Modular Function) - (time from Jenkins Function)", xlabel="shingles size (k)", ylabel="mean time difference (ms)")

# Show the plot
# plt.show()

# Save the plot
plt.savefig(path + '\\plots\\sig_time_modular_vs_jenkinsFunc.png', bbox_inches='tight')

# Clear and close the plot
plt.clf()