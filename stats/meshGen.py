import os
import re
import numpy as np
import pandas as pd
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# Open file where we are gonna put it all
dt = pd.read_csv(path + '\\data\\signature_nHashFun_k_sim.csv')
file = open(path + '\\data\\signature_nHashFun_mesh.csv', 'w')

# Shingles
i = dt.iloc[:, 1]
i = np.unique(i)

# hashFunctions
j = dt.iloc[:, 0]
j = np.unique(j)

#hashFun will be rows and Shingles will be cols
# Put null at first and then all shingle sizes at first row
for shingleNum in i:
    file.write(', ' + str(shingleNum))
file.write('\n')

# Fill with nHashFunctions at first col and then the values
for numHashFun in j:
    # For each hash function num get all rows with that function
    rows = dt.loc[dt['Number of Hash Functions'] == numHashFun]
    file.write(str(numHashFun))

    for shingleNum in i:
        row = rows.loc[rows.ix[:,1] == shingleNum]
        file.write(', ' + str(np.asscalar(row.ix[:,2])))
    file.write('\n')

file.close()