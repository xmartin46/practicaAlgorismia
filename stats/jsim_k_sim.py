import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\data\\jsim_k_sim.csv', 'w')
file.write('k, Jaccard Similarity' + '\n')

print('k, Jaccard Similarity')

# k = size of shingles
for k in range(21):
    out = subprocess.check_output([path + '\\algorithms\\jSim.exe', str(k)])
    out = str(k) + ', ' + (out.decode("utf-8"))
    print(out)
    file.write(out + '\n')

file.close()