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
ax = plt.axes(projection='3d')

# Importing the dataset
dt = pd.read_csv(path + '\\data\\signature_nHashFun_k_sim.csv')

# Plot the data
x = dt.iloc[:, 1] # Shingles
y = dt.iloc[:, 0] # nHashFun
z = dt.iloc[:, 2] # Similarity

ax.scatter(x,y,z, cmap='winter', c=x)

# ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='viridis', edgecolor='none', label='Signature Matrix Approximation', alpha=1.0)


# Set "tick" frequency in x axis
step = 1.0
minRange = int(np.min(x))
maxRange = int(np.max(x))+1
plt.xticks([x * step for x in range(minRange, maxRange)])
# ax.xaxis.set_major_locator(ticker.MultipleLocator(base=0.5))

# We change the fontsize of minor ticks label 
plt.tick_params(axis='x', which='major', labelsize=5)

# Set titles
ax.set_title("Signature Matrix Approximation")
ax.set_xlabel("shingle size (num chars)")
ax.set_ylabel("num Hash Functions used")
ax.set_zlabel("similarity (%)")

# Show the plot

plt.show()

# Save the plot
# plt.savefig('plot')

# Clear and close the plot
# plt.clf()