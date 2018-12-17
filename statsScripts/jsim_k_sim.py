import subprocess

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')

for pairs in pairsFile.readlines():

    pairs = pairs.rstrip('\n').split(" ")
    file = open(path + '\\data\\jsim_' + str(pairs[0]) + '_' + str(pairs[1]) + '.csv', 'w')
    file.write('k, JaccardSimilarity' + '\n')
    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\jSim.exe', str(k), str(pairs[0]), str(pairs[1]), str(0), str(1)])
        out = str(k) + ', ' + (out.decode("utf-8"))
        file.write(out + '\n')

    file.close()
pairsFile.close()

