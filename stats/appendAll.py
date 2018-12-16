import os
import re
import glob
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# find all files in path that match regular expression
files = [f for f in os.listdir(path + '\\data') if re.match(r'signature\_[0-9]+.*\.csv', f)]

# Open file where we are gonna put it all
file = open(path + '\\data\\signature_nHashFun_k_sim.csv', 'w')

file.write('NumberOfHashFunctions, k, JaccardSimilarity', end = '\n')
for fileName in files:
    f = open(path + '\\data\\' + fileName)
    f.readline()
    file.write(f.read())
    f.close()

file.close()
