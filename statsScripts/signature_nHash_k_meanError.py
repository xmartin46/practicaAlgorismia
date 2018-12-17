import subprocess
import pandas as pd
import numpy as np
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath



# n = number of hash functions applied to create signature matrix

# Importing the dataset
dtJS = pd.read_csv(path + '\\data\\jsim_k_meanSim.csv', sep='\s*,\s*')
dtSig = pd.read_csv(path + '\\data\\signature_nHash_k_meanSim_jenkinsFunc.csv', sep='\s*,\s*')

# Plot the data
hashFun = np.unique(dtSig.iloc[:, 0])
for n in hashFun:
    for k in range(16):
        rowInd = dtSig.index[(dtSig['NumberOfHashFunctions'] == n) & (dtSig['k'] == k)]
        rowJS = dtJS.index[dtJS['k'] == k]
        aprox = float(dtSig.loc[rowInd, 'JaccardSimilarity'])
        exact = float(dtJS.loc[rowJS, 'JaccardSimilarity'])
        dtSig.loc[rowInd, 'error'] = abs(aprox-exact)

dtSig.to_csv(path + '\\data\\sig_jsim_meanError_jenkinsFunc.csv', encoding='utf-8', index=False)



    