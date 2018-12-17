import subprocess

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')
numPair = 0
file = open(path + '\\data\\jsim_noSpaces_k_meanSim.csv', 'w')
file.write('k, Jaccard Similarity' + '\n')

sims = [0 for n in range(16)]
# noSpaces
for pairs in pairsFile.readlines():

    pairs = pairs.rstrip('\n').split(" ")

    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\jSim.exe', str(k), str(pairs[0]), str(pairs[1]), str(0), str(0)])
        sims[k] += float(out.decode("utf-8"))
        if numPair == 4:
                sims[k] /= 5
                out = str(k) + ', ' + str(sims[k])
                file.write(out + '\n')

    numPair += 1
file.close()
pairsFile.close()



# Spaces
numPair = 0
sims = [0 for n in range(16)]
pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')
file = open(path + '\\data\\jsim_yesSpaces_k_meanSim.csv', 'w')
file.write('k, Jaccard Similarity' + '\n')
for pairs in pairsFile.readlines():

    pairs = pairs.rstrip('\n').split(" ")

    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\jSim.exe', str(k), str(pairs[0]), str(pairs[1]), str(0), str(1)])
        sims[k] += float(out.decode("utf-8"))
        if numPair == 4:
                sims[k] /= 5
                out = str(k) + ', ' + str(sims[k])
                file.write(out + '\n')

    numPair += 1
file.close()
pairsFile.close()



