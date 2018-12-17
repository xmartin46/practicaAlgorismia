import subprocess

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'w')
numPairs = 5

for n in range(numPairs):
    out = subprocess.check_output([path + '\\algorithms\\genRandPairsOfNum.exe'])
    out = out.decode("utf-8").split(" ")
    file.write(str(out[0]) + ' ' + str(out[1]) + '\n')