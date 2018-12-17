import subprocess
import pandas as pd
import numpy as np
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath



# n = number of hash functions applied to create signature matrix

# Importing the dataset
dtJenk = pd.read_csv(path + '\\data\\signature_nHash_k_meanTime_jenkinsFunc.csv', sep='\s*,\s*')
dtMod = pd.read_csv(path + '\\data\\signature_nHash_k_meanTime.csv', sep='\s*,\s*')
dtMod['JaccardSimilarity'] = dtMod['JaccardSimilarity'] - dtJenk['JaccardSimilarity']

dtMod.to_csv(path + '\\data\\sig_time_modular_vs_jenkinsFunc.csv', encoding='utf-8', index=False)



    