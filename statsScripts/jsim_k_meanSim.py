import subprocess

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\data\\jsim_k_meanSim.csv', 'w')
file.write('k, Jaccard Similarity' + '\n')

pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')
sims = [0 for x in range(16)]
for pairs in pairsFile.readlines():
    pairs = pairs.rstrip('\n').split(" ")
    
    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\jSim.exe', str(k), str(pairs[0]), str(pairs[1]), str(0), str(1)])
        sims[k] += float((out.decode("utf-8")))

for k in range(16):
    sims[k] /= 5
    out = str(k) + ', ' + str(sims[k])
    file.write(out + '\n')
file.close()
pairsFile.close()